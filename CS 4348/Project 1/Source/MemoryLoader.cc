//Daniel Eisterhold
//CS4348 Project 1
//28 Sept. 2015

#include "MemoryLoader.h"

MemoryLoader::MemoryLoader() {
  path = "";
  currentAddress = 0;
}

MemoryLoader::MemoryLoader(std::string pathToFile) {
  path = pathToFile;
}

MemoryLoader::~MemoryLoader() {
  if(inputFile.is_open()) {
    inputFile.close();
  }
}

bool MemoryLoader::setFilePath(std::string pathToFile) {
  if(inputFile == 0) {
    path = pathToFile;
    return true;
  }
  else {
    fprintf(stderr, "Unable to set the path once the file has been opened\n");
    return false;
  }
}

void MemoryLoader::startParsing(int *ram, size_t size) {
  //Attempt to open the file
  inputFile.open(path.c_str());

  //Check to see if the file is open
  if(inputFile.is_open()) {
    //Buffer to hold data when we read a line from the file
    char lineBuffer[512];
    //Read a line from the file until you fill the buffer or reach a newline
    inputFile.getline(lineBuffer, 512, '\n');
    while((inputFile.gcount() > 0) && !inputFile.eof()) {
      //fprintf(stdout, "Parsed %d from line\n", parseLine(lineBuffer));
      parseLine(lineBuffer, ram, size);

      //Clear buffer for the next read
      memset(lineBuffer, 0x0, 512);

      //Read next line into buffer
      inputFile.getline(lineBuffer, 512, '\n');
    }

    //Close the file if it was opened
    inputFile.close();
  }
  else {
    fprintf(stderr, "Unable to open file\n");
  }
}

void MemoryLoader::parseLine(char *cstring, int *ram, size_t size) {
  char validChar[] = {'1','2','3','4','5','6','7','8','9','0','.'};
  char currentLetter;
  std::string cleanString = "";
  //Loop through the string
  for(uint cstringIndex = 0;;cstring++) {
    //Move to the next letter
    currentLetter = cstring[cstringIndex];
    
    //Break out of loop if we have reached the end of the string or whitespace
    if((currentLetter == '\0') || (currentLetter == ' ') || (currentLetter == '\t')) break;
    
    //Loop through the valid characters
    for(uint validCharIndex = 0; validCharIndex <= (sizeof(validChar)/sizeof(validChar[0])); validCharIndex++) {
      //If find a match append it to the string
      if(currentLetter == validChar[validCharIndex]) {
	cleanString += currentLetter;
      }
    }
  }
  //If the string is not empty
  if(cleanString.length() > 0) {
    //If the beginning of the string
    if(cleanString[0] == '.') {
      //Change the current address
      currentAddress =  atoi(cleanString.substr(1).c_str());
    }
    else {
      //fprintf(stdout, "Loading \"%d\" into address %d\n", atoi(cleanString.c_str()), currentAddress);
      
      //Store integer into memory
      ram[currentAddress] = atoi(cleanString.c_str());

      //Increment address
      currentAddress++;
    }
  }
}
