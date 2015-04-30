This program demonstrates the use of bison, flex, and implicit rules with make.

Compiling:
type "make"
To compile you will need both flex and bison installed

Running:
//Tokenizing the input file
type "./scanner < input.txt"

//Parsing the input file
type "./parse < input.txt"