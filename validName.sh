#!/bin/bash

echo "Testing Valid Names..."
./directory add "Bruce Schneier" 12345
./directory add "Schneier, Bruce" 12345
./directory add "Schneier, Bruce Wayne" 12345 
./directory add "O'Malley, John F." 12345  
./directory add "John O'Malley-Smith" 12345 
./directory add "Cher" 12345
echo "6 Tests for name inputs were executed.." 
