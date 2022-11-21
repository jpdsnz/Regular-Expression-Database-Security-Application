#!/bin/bash

echo "Testing Invalid Names..."
./directory add "Ron O’’Henry" 12345
./directory add "Ron O’Henry-Smith-Barnes" 12345
./directory add "L33t Hacker" 12345 
./directory add "<Script>alert(“XSS”)</Script>" 12345  
./directory add "Brad Everett Samuel Smith" 12345 
./directory add "select * from users" 12345
echo "6 Tests for name inputs were executed.." 
