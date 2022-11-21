#!/bin/bash

g++ phoneBook.cpp -o directory -l sqlite3
sudo chown root directory
sudo chmod 4755 directory
./revoke.sh
echo "Compilation complete..."
echo "Files are accessible by Seed account!"
 
