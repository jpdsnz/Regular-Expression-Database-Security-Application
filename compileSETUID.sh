#!/bin/bash
#Setting Permissions for files
echo "Now setting permissions..."
sudo chown seed compile.sh
sudo chmod 755 compile.sh
sudo chown seed validName.sh
sudo chmod 755 validName.sh
sudo chown seed invalidName.sh
sudo chmod 755 invalidName.sh
sudo chown seed validPhone.sh
sudo chmod 755 validPhone.sh
sudo chown seed invalidPhone.sh
sudo chmod 755 invalidPhone.sh
sudo chown seed evoke.sh
sudo chmod 755 evoke.sh
sudo chown seed revoke.sh
sudo chmod 755 revoke.sh
sudo chown root audit.LOG
sudo chown root config.cfg
sudo chown root phoneDirectory.db
sudo chmod 700 audit.LOG
sudo chmod 700 config.cfg
sudo chmod 700 phoneDirectory.db
#Compile program
echo "Now compiling program, please wait..."
g++ phoneBook.cpp -o directory -l sqlite3
sudo chown root directory
sudo chmod 4755 directory
echo "Compilation complete..."
echo "Only Root can open audit.LOG, phoneDirectory.db, and config.cfg!"
 
