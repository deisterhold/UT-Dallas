//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

// Location of gawk
const char gawkBinary[] = "/usr/bin/awk";

// Location of gawk code file
const char gawkInputFile[] = "awk.code";

// Location of file containing numbers
const char numbersInputFile[] = "numbers.txt";

int main(int argc, char* argv[]) {
  // Output the location of gawk
  cout<<"gawk at: "<<gawkBinary<<endl;

  // Variable to hold the pipe we will be opening
  FILE *input;
  
  // Variable to hold the command that will be called
  string gawkVersionCommand = gawkBinary;
  // Add the flag to get the version
  gawkVersionCommand += " --version";
  
  // Output the command we are going to call
  cout<<"Shellcmd1: "<<gawkVersionCommand<<endl;

  // Variable to hold the second command we will call                                                                 
  string gawkAddColumnsCommand = gawkBinary;

  // Add flag to command so gawk can use our input file                                                              
  gawkAddColumnsCommand += " -f ";
  gawkAddColumnsCommand += gawkInputFile;

  // Add to the command the file that we want gawk to look through                                                   
  gawkAddColumnsCommand += " ";
  gawkAddColumnsCommand += numbersInputFile;

  // Output the second command we will call                                                                           
  cout<<"Shellcmd2: "<<gawkAddColumnsCommand<<endl;

  // Open a pipe for reading and give it the command to call
  input = popen(gawkVersionCommand.c_str(), "r");

  // If the pipe was unable to be opened
  if(input == NULL) {
    cerr<<"Unable to open pipe to shell."<<endl;
    return 1;
  }
  else {
    // Buffer to hold the data the pipe returned
    char buffer[1024];

    // Output a message about the first call
    cout<<"\nThe first call to gawk returned:\n"<<endl;
    
    // While there is data available from the pipe read it
    while(fgets(buffer, 1024, input)) {
      // Output the data read from the pipe
      cout<<buffer;
    }
    // Close the pipe
    pclose(input);
  }
  
  // Open a pipe with the command we want to call
  input = popen(gawkAddColumnsCommand.c_str(), "r");
  
  // If the pipe was unable to be opened
  if(input == NULL) {
    cerr<<"Unable to open pipe to shell."<<endl;
    return 1;
  }
  else {
    // Variables to hold the sums and a buffer for the data returned
    int num1;
    int num2;
    char buffer[1024];

    // Output a message
    cout<<"\nThe second call to gawk returned: ";

    // Read the first value from the pipe
    fgets(buffer, 1024, input);

    // Convert the char array to an int
    num1 = atoi(buffer);
    
    // Add a space between the numbers
    cout<<num1<<" ";

    // Read the second value from the pipe
    fgets(buffer, 1024, input);

    // Convert the char array to an int
    num2 = atoi(buffer);

    // Output the integer
    cout<<num2<<endl;

    // Output the sum of column 1
    cout<<"\nThe sum of Column 1 is: "<<num1<<endl;

    // Output the sum of column 4
    cout<<"The sum of Column 4 is: "<<num2<<endl;

    // Output the sum of both the columns
    cout<<"The Sum of the two numbers is: "<<num1 + num2<<endl;

    pclose(input);
  }
  return 0;
}
