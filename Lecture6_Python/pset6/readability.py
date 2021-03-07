from cs50 import get_string
import string
text = get_string("Text: ")
#text ="Congratulations! Today is your day. You're off to Great Places! You're off and away!"
letters = 0
words = 1
sentences = 0
for i in text:
    if i == " ":
        words += 1
    if i =="!" or i=="." or i=="?":
        sentences += 1
    if i in string.ascii_lowercase or i in string.ascii_uppercase:
        letters+=1

L= letters/words*100
S= sentences/words*100
index = round(0.0588 * L - 0.296 * S - 15.8)
if (index < 1):
    print("Before Grade 1")
elif (index >=1 and index < 16):
    print("Grade ", index)
else:
    print("Grade 16+")