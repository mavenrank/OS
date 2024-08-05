#!/bin/bash

a=5
b=3

sum=$((a + b))
echo "Sum: $sum"

product=$(expr $a \* $b)
echo "Product: $product"

difference=$(expr $a \- $b)
echo "Difference: $difference"

