#!/bin/bash

echo "create 1 file : 'test'"
echo "execute with './test'"
gcc test.c -o test
chmod +x test
./test "dpt2020.csv"