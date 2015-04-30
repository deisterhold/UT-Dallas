//#Daniel Eisterhold                                                           
//dte130030@utdallas.edu                                                       //CS 3376.502  
#include <iostream>

#include "program2.h"

using namespace std;

int main(int argc, char *argv[]) {
  //Output the number of arguments
  cout<<"Number of arguments: "<<argc<<endl;
    //Loop through the array and print out all the arguments
    for(int argument = 0; argument < argc; argument++) {
      cout<<"Argument #"<<argument+1<<": "<<argv[argument]<<endl;
    }
  
  program2 myProgram = program2();

  return 0;
}
