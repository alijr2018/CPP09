#!/bin/bash

make

echo "===== VALID ====="

./RPN "8 9 * 9 - 9 - 9 - 4 - 1 +"

./RPN "7 7 * 7 -"

./RPN "1 2 * 2 / 2 * 2 4 - +"


echo "===== INVALID ====="

./RPN "(1 + 1)"

./RPN "1 2"

./RPN "+"

./RPN "1 +"

./RPN "1 0 /"

./RPN "1 a +"

./RPN "1.5 2 +"

./RPN "-1 2 +"

