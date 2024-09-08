-- For more information about a crime day.
SELECT description FROM crime_scene_reports WHERE street ='Humphrey Street' AND month=7 AND year=2023 AND day=28;

-- To see what witnesses said on the day of the robbery.
SELECT name, transcript FROM interviews WHERE month=7 AND year=2023 AND day=28 AND transcript LIKE "%bakery%";

-- Suspects from bakery security logs
SELECT people.name, bakery_security_logs.activity, bakery_security_logs.license_plate FROM bakery_security_logs JOIN people ON bakery_security_logs.license_plate=people.license_plate WHERE month=7 AND year=2023 AND day=28 AND hour =10 AND minute BETWEEN 15 AND 25;

-- Suspects from ATM transactions
SELECT people.name, atm_transactions.transaction_type FROM people JOIN bank_accounts ON people.id=bank_accounts.person_id JOIN atm_transactions ON bank_accounts.account_number=atm_transactions.account_number WHERE atm_transactions.year=2023 AND atm_transactions.month=7 AND atm_transactions.day=28 AND atm_location='Leggett Street';

-- Update this column by people names.
-- https://www.sqlitetutorial.net/sqlite-update/
UPDATE phone_calls SET caller = people.name FROM people WHERE people.phone_number=phone_calls.caller;
UPDATE phone_calls SET receiver = people.name FROM people WHERE people.phone_number=phone_calls.receiver;

-- Identifying the callers and receivers on the day of the theft, which took less than a minute.
SELECT id, caller, receiver FROM phone_calls WHERE month=7 AND year=2023 AND day=28 AND duration<60;

-- Determine the nearest plane that took off the day after the theft.
SELECT * FROM flights WHERE day=29 AND month=7 AND year=2023 ORDER BY hour LIMIT 1;

-- Identify the thief's interface.
-- Thanks for CS50 DUCK, It helps me with this query. :)
SELECT d.city AS "Thief's interface" FROM airports o JOIN flights ON o.id=flights.origin_airport_id JOIN airports d ON d.id=flights.destination_airport_id WHERE flights.day=29 AND flights.month=7 AND flights.year=2023 ORDER BY flights.hour LIMIT 1;

-- The name of the thief and her assistant
SELECT caller AS Thief, receiver AS Assistant FROM phone_calls WHERE id=233;
