#Daniel Eisterhold                                                             #dte130030@utdallas.edu                                                        #CS 3376.502  

#!/bin/bash

#Compile the program only
echo "Compiling program into object files"
g++ -c program1.cpp -o program1.o

#Link object files
echo "Linking object files into executable"
g++ program1.o -o myprogram