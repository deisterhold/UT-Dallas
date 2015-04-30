// Daniel Eisterhold
// dte130030@utdallas.edu
// CS 3376.502

#include <iostream>
#include <fstream>
#include <map>
#include "tclap/CmdLine.h"

using namespace std;

// Function for converting bool to string
const char* Bool2String(bool val) {
  return val ? "true" : "false";
}

int main(int argc, char *argv[]) {

  // Create enum to get access to the flags in the map more easily
  enum flag {
    lower,
    upper,
    outputFileName,
    inputFileName
  };

  // Create map to hold the results of the flags
  map<int,std::string> flags;

  // Put everything in a try block because the parse can/will throw exceptions
  try {
    // Create a command line parsing object
    TCLAP::CmdLine cmd("Program #2",' ',"1.0.0");

    // Create the flags in the order we expect them to be input on the command line
    // Create lower case flag
    TCLAP::SwitchArg lowerCase("l","lower","Convert all text to lowercase",cmd,false);

    // Create upper case flag
    TCLAP::SwitchArg upperCase("u","upper","Convert all text to uppercase",cmd,false);
    
    // Create the output file flag
    TCLAP::ValueArg<string> outputFile("o","output","The name of the output file", false, "output.txt", "output filename");

    // Add the output flag to the parser
    cmd.add(outputFile);

    // Create the input file flag
    TCLAP::UnlabeledValueArg<string> inputFile("inputFile","The name of the input file",true,"inputFile.txt","input filename", false);
    
    // Add the input flag to the parser
    cmd.add(inputFile);

    // Start parsing the arguments
    cmd.parse(argc, argv);

    // Store the values of the flags into a map using an enum for an accessor
    flags[lower] = Bool2String(lowerCase.getValue());
    flags[upper] = Bool2String(upperCase.getValue());
    flags[outputFileName] = outputFile.getValue();
    flags[inputFileName] = inputFile.getValue();

    // Check that the lowerCase and upperCase flags are mutually exclusive
    if((flags[lower] == "true") && (flags[upper] == "true")) {
      cerr<<"Lower case and upper case flags are mutually exclusive."<<endl;
      cmd.getOutput()->usage(cmd);
      exit(1);
    }

    ifstream input;
    ofstream output;

    // Open the input file
    input.open(flags[inputFileName].c_str());

    // Output the output file
    output.open(flags[outputFileName].c_str());

    // Check if the files opened successfully
    if(!input.is_open()) {
      cerr<<"Filename: "<<flags[inputFileName].c_str()<<endl;
      cerr<<"Error opening input file"<<endl;
      exit(1);
    }
    if(!output.is_open()) {
      cerr<<"Filename: "<<flags[outputFileName].c_str()<<endl;
      cerr<<"Error opening output file"<<endl;
      exit(1);
    }

    // Temporary variable to hold a line of data
    char temp;
    while(input.get(temp)) {
      if(flags[lower] == "true") {
        output<<(char)tolower(temp);
      }
      else if(flags[upper] == "true") {
        output<<(char)toupper(temp);
      }
      else {
        output<<(char)temp;
      }
    }

    // Close the input file
    input.close();

    // Close the output file
    output.close();

  }
  catch(TCLAP::ArgException &e) {
    cerr<<"Error: "<<e.error()<<" for argument "<<e.argId()<<endl;
  }

  return 0;
}
