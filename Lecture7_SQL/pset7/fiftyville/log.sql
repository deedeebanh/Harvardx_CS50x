-- Keep a log of any SQL queries you execute as you solve the mystery.

-- Retrieve the Crime Scene Reports
SELECT * from crime_scene_reports WHERE year = 2020 AND month = 7 AND day = 28 AND street = "Chamberlin Street";

-- Retrieve the Interview from the witnesses
SELECT * from interviews WHERE year = 2020 AND month = 7 AND day = 28;

-- Retrieve the Security Log to find the car plate number.
SELECT * from courthouse_security_logs WHERE year = 2020 AND month = 7 AND day = 28 AND hour = 10;

-- Retrieve from atm_transactions around the time when the thief left the courthouse
-- According to Eugene it was the ATM on Fifer Street
SELECT * from atm_transactions WHERE year = 2020 AND month = 7 AND day = 28 AND atm_location = "Fifer Street";

-- Narrow down to People that left the courthouse and also visit the ATM on Fifer Street.
SELECT people.name, people.phone_number FROM atm_transactions
JOIN courthouse_security_logs ON people.license_plate = courthouse_security_logs.license_plate
JOIN people ON bank_accounts.person_id = people.id
JOIN bank_accounts ON atm_transactions.account_number = bank_accounts.account_number
WHERE atm_transactions.year = 2020 AND atm_transactions.month = 7
AND atm_transactions.day = 28 AND atm_transactions.atm_location = "Fifer Street"
AND atm_transactions.transaction_type = "withdraw"
AND courthouse_security_logs.hour = 10 AND courthouse_security_logs.activity = "exit"
AND courthouse_security_logs.minute >= 15 AND courthouse_security_logs.minute <= 25

INTERSECT
-- Find out who is leaving Fiftyville on the day after
SELECT people.name, people.phone_number FROM airports
JOIN flights ON airports.id = flights.origin_airport_id
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
WHERE airports.city = "Fiftyville" AND flights.year = 2020
AND flights.month = 7 AND flights.day = 29

INTERSECT
-- Eugene said he recognizes the Thief
-- The only person Eugene knows/phoned to is Ernest!
SELECT people.name , people.phone_number FROM people
JOIN phone_calls ON people.phone_number = phone_calls.caller
WHERE phone_calls.receiver = (SELECT phone_number from people WHERE people.name = "Eugene");

-- Ernest is Leaving Fiftyville to London
SELECT flights.id, city FROM airports
JOIN flights ON flights.destination_airport_id = airports.id
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON people.passport_number = passengers.passport_number
WHERE people.name = "Ernest";

-- Find the accomplice
-- Find who's also on the same flight that day
SELECT people.name, atm_transactions.transaction_type FROM flights
JOIN passengers ON flights.id = passengers.flight_id
JOIN people ON passengers.passport_number = people.passport_number
JOIN bank_accounts ON people.id = bank_accounts.person_id
JOIN atm_transactions ON bank_accounts.account_number = atm_transactions.account_number
WHERE flights.id = 36 AND atm_transactions.day = 28;

SELECT people.name FROM people
JOIN phone_calls ON people.phone_number = phone_calls.receiver
WHERE phone_calls.caller = (SELECT phone_number from people WHERE people.name = "Ernest")
AND phone_calls.day = 28 ORDER BY phone_calls.duration;