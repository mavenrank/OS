#!/bin/bash
echo "Enter a number"
read num1
echo "Enter another number"
read num2

if [ $num1 -gt $num2 ]; 
    then echo "$num1 is greater than $num2"
else 
    echo "$num2 is greater than $num1"
fi