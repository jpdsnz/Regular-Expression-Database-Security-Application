#!/bin/bash

echo "Testing Valid Phone Numbers..."
./directory add John "12345"
./directory add John "(703)111-2121"
./directory add John "670-123-4567"
./directory add John "1-670-123-4567"
./directory add John "670 123 4567"
./directory add John "670.123.4567"
./directory add John "1 670 123 4567"
./directory add John "1.670.123.4567"
./directory add John "123-1234"
./directory add John "+1(703)111-2121"
./directory add John "+32 (21) 212-2324"
./directory add John "1(703)123-1234"
./directory add John "011 701 111 1234"
./directory add John "12345.12345"
./directory add John "011 1 703 111 1234"
./directory add John "11 11 11 11"
./directory add John "11.11.11.11"
./directory add John "45 11 11 11 11"
./directory add John "45.11.11.11.11"
./directory add John "1111 1111"
./directory add John "1111.1111"
./directory add John "45 1111 1111"
./directory add John "45.1111.1111"

echo "23 Tests for phone inputs were executed.."