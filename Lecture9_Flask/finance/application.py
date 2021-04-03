import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash

from datetime import datetime
import re

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True


# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")

# export API_KEY=pk_10acdd5224604ce085364e30c6c1a1a5

@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        return redirect("/")
    else:
        user_id = session["user_id"]
        stocks = db.execute("SELECT * FROM users JOIN stocks ON users.id=stocks.stock_id WHERE id=?",user_id)
        rows = db.execute("SELECT cash FROM users WHERE id=?",user_id)
        cash = rows[0]["cash"]
        costPerStock = 0
        costTotal = []
        for stock in stocks:
            symbol = stock["symbol"]
            shares = stock["shares"]
            quote = lookup(symbol)
            name = lookup(symbol)["name"]
            price = lookup(symbol)["price"]
            cost = shares*price
            costTotal.append(cost)
            stock["name"] = name
            stock["shares"] = shares
            stock["price"] = usd(price)
            stock["total"] = usd(cost)
        principle = cash+sum(costTotal)
        return render_template("index.html",stocks=stocks, cash=usd(cash), principle=usd(principle))

@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide Stock Ticker symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide shares", 400)
        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares")
        try:
            shares=int(shares)
        except:
            return apology("shares must be an integer", 400)
        if shares <= 0:
            return apology("input must be be positive", 400)

        quote = lookup(symbol)
        if quote==None:
            return apology("Symbol is Invalid.", 400)

        price_per_share = quote["price"]
        name = quote["name"]

        user_id = session["user_id"]

        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cashAvai = rows[0]["cash"]
        total = price_per_share * shares
        cash = cashAvai - total

        #First Check if Enough Money
        if cash < 0:
            return apology("You don't have enough cash", 400)
        else:
            # Update cash
            db.execute("UPDATE users SET cash  = ? WHERE id = ?", cash, user_id)

        #Check if user already bought the same stock before
        rows = db.execute("SELECT symbol FROM stocks WHERE symbol = ?", symbol)

        #if stock exists already update the stock
        if len(rows) == 1:
            shares_old = db.execute("SELECT shares FROM stocks WHERE symbol = ?", symbol)
            shares_new = shares_old[0]["shares"]+shares
            db.execute("UPDATE stocks SET shares  = ? WHERE symbol = ?", shares_new, symbol)
        else:
            # Add the user's entry into the database
            db.execute("INSERT INTO stocks (stock_id, symbol, shares) VALUES (?, ?, ?)", user_id, symbol, shares)

        date = datetime.now()
        db.execute("INSERT INTO history (history_id, symbol, shares, action, datetime) VALUES (?, ?, ?, ?, ?)", user_id, symbol, shares, "Buy", date)
        flash("Stocks bought!")

        # Redirect user to home page
        return redirect("/")
    else:
        return render_template("buy.html")

@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        history = db.execute("SELECT * FROM history ORDER BY datetime DESC")
        return render_template("history.html", history=history)
    # User reached route via GET (as by clicking a link or via redirect)
    else:
        history = db.execute("SELECT * FROM history ORDER BY datetime DESC")
        return render_template("history.html", history=history)

@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 400)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide Stock Ticker symbol", 400)
        symbol = request.form.get("symbol").upper()
        quote=lookup(symbol)
        if quote==None:
            return apology("Invalid symbol")
        name = quote["name"]
        price = quote["price"]

        return render_template("quoted.html", symbol=symbol,name=name,price=usd(price))
    else:
        return render_template("quote.html")

@app.route("/addfund", methods=["GET", "POST"])
@login_required
def addfund():
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("addfund"):
            return apology("must provide fund amount", 400)
        user_id = session["user_id"]
        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cash = rows[0]["cash"]
        fund = request.form.get("addfund",type=float)
        cashupdate=cash+fund
        db.execute("UPDATE users SET cash  = ? WHERE id = ?", cashupdate, user_id)
        flash("Fund Added!")
        return redirect("/")
    else:
        return render_template("addfund.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure username is not already existing
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))
        if len(rows) == 1:
            return apology("Sorry, your username is already taken. Please enter another username.", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Ensure retype password was submitted
        elif not request.form.get("confirmation"):
            return apology("must provide retype password", 400)

        #Ensure retype password is the same to password
        elif request.form.get("password") != request.form.get("confirmation"):
            return apology("Sorry, your passwords did not match", 400)

        # Add the user's entry into the database
        db.execute("INSERT INTO users (username, hash) VALUES(?, ?)", request.form.get("username"), generate_password_hash(request.form.get("password")))
        flash("You were successfully registered!")

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("register.html")

@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide Stock Ticker symbol", 400)
        if not request.form.get("shares"):
            return apology("must provide shares", 400)

        symbol = request.form.get("symbol").upper()
        shares = request.form.get("shares", type=int)
        if shares < 0:
            return apology("input must be be positive", 400)
        quoteoutputs = lookup(symbol)
        price_per_share = quoteoutputs["price"]
        user_id = session["user_id"]

        rows = db.execute("SELECT cash FROM users WHERE id = ?", user_id)
        cashAvai = rows[0]["cash"]
        name = quoteoutputs["name"]

        #Cash Gain after Selling
        total = price_per_share * shares
        cash = cashAvai + total

        #Check if user already bought the same stock before
        rows = db.execute("SELECT symbol FROM stocks WHERE symbol = ?", symbol)

        #if user has the stock
        if len(rows) != 1:
            return apology("You don't have this stock", 400)

        #First Check if Enough Shares
        shares_old = db.execute("SELECT shares FROM stocks WHERE symbol = ?", symbol)
        if shares > shares_old[0]["shares"]:
            return apology("You don't have enough shares to sell", 400)

        #if no more shares left, delete the entire row
        elif shares == shares_old[0]["shares"]:
            db.execute("DELETE FROM stocks WHERE symbol = ?", symbol)

        #else, update all variables
        else:
            shares_old = db.execute("SELECT shares FROM stocks WHERE symbol = ?", symbol)
            shares_new = shares_old[0]["shares"]-shares
            db.execute("UPDATE stocks SET shares  = ? WHERE symbol = ?", shares_new, symbol)

        db.execute("UPDATE users SET cash  = ? WHERE id = ?", cash, user_id)

        date = datetime.now()
        db.execute("INSERT INTO history (history_id, symbol, shares, action, datetime) VALUES (?, ?, ?, ?, ?)", user_id, symbol, shares, "Sell", date)
        flash("Stocks sold!")

        return redirect("/")
    else:
        user_id = session["user_id"]
        stocks = db.execute("SELECT symbol FROM users JOIN stocks ON users.id=stocks.stock_id WHERE id=?",user_id)
        return render_template("sell.html",stocks=stocks)

def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)
