#!/bin/bash

sudo chown root audit.LOG
sudo chown root config.cfg
sudo chown root phoneDirectory.db
sudo chmod 700 audit.LOG 
sudo chmod 700 config.cfg
sudo chmod 700 phoneDirectory.db

echo "Files changed back to Root privileges..."
 
