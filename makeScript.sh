#!/bin/bash

echo "                                     _____         ______   __   ___ ___                                    
                                    / ____|  /\   |  ____| /_ | / _ \__ \                                   
  ______ ______ ______ ______ _____| (___   /  \  | |__     | || | | | ) |_____ ______ ______ ______ ______ 
 |______|______|______|______|______\___ \ / /\ \ |  __|    | || | | |/ /______|______|______|______|______|
                                    ____) / ____ \| |____   | || |_| / /_                                   
                                   |_____/_/    \_\______|  |_(_)___/____|                                  
                                                                                        "
echo "\n\n"

echo "Create 2 files : 'table' and 'listChained'"
echo "execute with './table dpt2020.csv' or './listChained dpt2020.csv'"
gcc -o table table.c
gcc -o listChained listChained.c
sudo chmod +x table
sudo chmod +x listChained