#Daniel Eisterhold
#dte130030@utdallas.edu
#CS 3376.502

#!/bin/bash

echo "Running program."
echo "Sending stdout to stdout.log"
echo "Sending stderr to stderr.log"

./myprogram -i testArgument1 -f testArgument2 >stdout.log 2>stderr.log

echo "Appending stdout to stdout.log"
echo "Appending stderr to stderr.log"
./myprogram -i anotherArg -f argHere >>stdout.log 2>>stderr.log

echo "Appending stdout to stdout.log"
echo "Appending stderr to stderr.log"
./myprogram -f argThere >>stdout.log 2>>stderr.log

echo "Appending stdout to stdout.log"
echo "Appending stderr to stderr.log"
./myprogram -i palceArgHere >>stdout.log 2>>stderr.log