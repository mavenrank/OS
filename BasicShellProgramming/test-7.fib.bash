#!/bin/bash

first=0
second=1

read -p "Enter the number of terms:" n
echo "Fibonacci series up to $n terms:"
echo $first
echo $second
count=2
while [ $count -lt $n ]; do
    temp=`expr $first + $second`
    echo $temp
    first=$second
    second=$temp
    count=$((count + 1))
done

