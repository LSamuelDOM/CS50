-- Keep a log of any SQL queries you execute as you solve the mystery.

-- My start was with a search on crime scene reports where I want to found only theft cases.
SELECT *
FROM crime_scene_reports
WHERE description
LIKE 'Theft%';
-- I found any answer where the duck was theft, Hemphrey Street, and the date/time, 2021/07/28, 10:15 AM, another thing I got, in Interviews had three witnesses who were present at the same time.

-- As said on description before, second step was looking into Interviews.
SELECT *
FROM interviews
WHERE transcript
LIKE '%Bakery%'
AND day = 28
AND month = 7
AND year = 2021;
-- Now I have all three witnesses transcripts.
-- Fist one, by Ruth, who said about time when thief left Bakery, was about 10 minutes after the theft.
-- Second one, by Eugene, he can't reconize thief by name, but early he saw the same thief at ATM on Leggett Street, the thief was withdrawing some money.
-- Third one, by Raymon, is about what the thief did after left Bakery, he make a call, to somebody, and said to buy the earliest flight out of Fiftyville, tomorrow, this call was less than one minute.

-- My next step was get all names who used the ATM at same day as criminal day.
SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021;
-- With this Query I got a list of names, with everybody who used ATM on day 2021/07/28.
-- My suspect list now is this name list: Bruce, Kaelyn, Diana, Brooke, Kenny, Iman, Luca, Taylor, Benista.

-- For now I searched about Raymon interview, who said the thief was buying the first flight out of city, on date 2021/07/29.
SELECT *
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1;
-- This command returns everything about the first flight of this date.
-- Now I have a flight id(36), origin airport(8) and destination airport(4) of this specific flight.

-- To get a city where this airplane will go, I used this Query:
SELECT city
FROM airports
JOIN flights
ON airports.id = flights.destination_airport_id
WHERE flights.id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1);
-- For now I have one answer, where the thief escaped, City = New York City.

-- I need to know, everbody that was on this flight, to make a list of names, I run this Query:
SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1);
-- Now I got a new list of suspects, this list is: Doris, Sofia, Bruce, Edward, Kelsey, Taylor, Kenny, Luca.

-- I have two suspects list, one got by ATM, and another by Flight, but the thief has to be in both, to check it:
SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1));
-- Now I have a better list, with four names only: Bruce, Kenny, Luca, Taylor.
-- All in this list was in ATM and Flight.

-- Using my last big clue, gived by Raymond, thief calls was less than one minute, and was made at date 2021/07/28:
SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60;
-- Now I have another list of names, everybody who did a call less than 1 minute and at same day as described by Raymond: Sofia, Kelsey, Bruce, Kelsey, Taylor, Diana, Carina, Kenny, Benista.

-- I have two suspects lists of names, to merge it again:
SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1)
AND name IN (SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60
AND name IN (SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit'))));
-- With this big command, I can merge the list of callers, flight and ATM, names, to see who was in all places.
-- This list contain: Bruce, Kenny, Taylor.

-- Now I have a small list of names, where all names was in flight, and ATM, and made a call with less than 60s, but I don't know if they was in Bakery, at 10:15 AM, and exit less than 10 minutes after it:
SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit');
-- Now I have a list with some names, who was in Bakery, and exit between the theft time and 10 minutes later.
-- This list contain: Vanessa, Barry, Iman, Sofia, Luca, Diana, Kelsey, Bruce.

-- Finally I got the thief, Bruce, because my suspects was Bruce, Kenny and Taylor, but only Bruce was in Bakery and exit less than 10 minutes later the theft.

-- Command to get thief name in one Query:
SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1)
AND name IN (SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60
AND name IN (SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit'))));


-- But I need to find who acomplice Bruce, for it:
SELECT name
FROM people
WHERE phone_number = (SELECT receiver
FROM phone_calls
WHERE caller = (SELECT phone_number
FROM people
WHERE name = 'Bruce')
AND day = 28
AND month = 7
AND year = 2021
AND duration < 60);
-- This command will return Robin name, that is the person who Bruce called less than 1 minute, at date 2021/07/28

-- Command to get thief accomplice name in one Querry:
SELECT name
FROM people
WHERE phone_number = (SELECT receiver
FROM phone_calls
WHERE caller = (SELECT phone_number
FROM people
WHERE name = (SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1)
AND name IN (SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60
AND name IN (SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit'))))))
AND day = 28
AND month = 7
AND year = 2021
AND duration < 60);


-- Command to get thief and his accomplice names in one Querry:
SELECT name
FROM people WHERE name = (SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1)
AND name IN (SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60
AND name IN (SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit')))))
OR name = (SELECT name
FROM people
WHERE phone_number = (SELECT receiver
FROM phone_calls
WHERE caller = (SELECT phone_number
FROM people
WHERE name = (SELECT name
FROM people
JOIN bank_accounts
ON people.id = bank_accounts.person_id
JOIN atm_transactions
ON bank_accounts.account_number = atm_transactions.account_number
WHERE atm_location = 'Leggett Street'
AND day = 28
AND month = 7
AND year = 2021
AND name IN (SELECT name
FROM people
JOIN passengers
ON people.passport_number = passengers.passport_number
JOIN flights
ON passengers.flight_id = flights.id
WHERE flight_id = (SELECT id
FROM flights
WHERE day = 29
AND month = 7
AND year = 2021
ORDER BY hour ASC
LIMIT 1)
AND name IN (SELECT name
FROM people
JOIN phone_calls
ON people.phone_number = phone_calls.caller
WHERE day = 28
AND month = 07
AND year = 2021
AND duration < 60
AND name IN (SELECT name
FROM people
WHERE license_plate IN (SELECT license_plate
FROM bakery_security_logs
WHERE day = 28
AND month = 7
AND hour = 10
AND minute >= 15
AND minute <= 25
AND activity = 'exit'))))))
AND day = 28
AND month = 7
AND year = 2021
AND duration < 60));
-- I know this can be better desing but it was just a test to see if I can get both at same time, what a big code xD.