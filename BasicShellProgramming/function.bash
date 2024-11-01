#!/bin/bash
add (){
    num1=$1
    num2=$2
    echo "Sum of the two numbers : $((num1+num2))"
}
echo "enter a number : "
read num1
echo "enter another number : "
read num2
add $num1 $num2
