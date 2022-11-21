#!/bin/bash

sudo chown seed audit.LOG
sudo chown seed config.cfg
sudo chown seed phoneDirectory.db
sudo chmod 664 audit.LOG 
sudo chmod 664 config.cfg
sudo chmod 664 phoneDirectory.db

echo "Files changed back to seed privileges..."
 
