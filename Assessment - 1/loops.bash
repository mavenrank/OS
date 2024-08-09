#!/bin/bash

for i in 1 2 3 4 5
do
  echo "Number: $i"
done

counter=1
while [ $counter -le 5 ]
do
  echo "Counter: $counter"
  ((counter++))
done

counter=1
until [ $counter -gt 5 ]; do
    echo "Counter: $counter"
    ((counter++))
done

echo "Enter a character: "
read char
case $char in
  [a-z] )
    echo "You entered a lowercase letter."
    ;;
  [A-Z] )
    echo "You entered an uppercase letter."
    ;;
  [0-9] )
    echo "You entered a digit."
    ;;
  * )
    echo "You entered a special character."
    ;;
esac
