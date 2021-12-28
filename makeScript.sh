#!/bin/bash

echo "create 1 file : 'test'"
echo "execute with './test'"
gcc -o test test.c
chmod +x test
./test