//Daniel Eisterhold
//CS4348 Project 1
//17 Sept. 2015

#include "Memory.h"

Memory::Memory() {
  memset(ram, 0x00, sizeof(ram)/sizeof(ram[0]));
  releaseMemory = false;
}

Memory::~Memory() {
}

int Memory::read(int address) {
  if(address < RAM_SIZE && address >= 0) {
    return ram[address];
  }
  else {
    fprintf(stderr,"Memory Read Access Violation. Address: %d does not exist.\n", address);
    return 0;
  }
}

void Memory::write(int address, int data) {
  if(address < RAM_SIZE && address >= 0) {
    ram[address] = data;
  }
  else {
    fprintf(stderr,"Memory Write Access Violation. Address: %d does not exist.\n", address);
  }
}

void Memory::setBus(BUS *bus) {
  //Set the data bus
  dataBus = bus;
}

void Memory::load(std::string fileLocation) {
  //Load contents of file into memory                                                                                      
  fprintf(stdout, "Loading \"%s\" into memory\n", fileLocation.c_str());
  
  //Create a memory loader and pass it the location of the input file
  MemoryLoader *loader = new MemoryLoader(fileLocation);
  
  //Start parsing the file and pass it the memory array
  loader->startParsing(ram, RAM_SIZE);

  fprintf(stdout, "Done loading into memory\n");
}

void Memory::start() {
  //Before processing and requests make sure to get the ready command from the CPU
  while(dataBus->read() != "READY") {
    //Wait a little before checking again
    usleep(1000000);
  }

  //Respond back to CPU stating the Memory is ready
  dataBus->write("READY");

  //Loop until flag is flipped
  while(!releaseMemory) {
    //Read command from bus and process
    processRequest(dataBus->read());
  }
}

void Memory::dump(bool hex) {
  if(hex) {
    for(int address = 0; address < RAM_SIZE; address++) {
      fprintf(stdout, "Address: 0x%.4x Data: 0x%x\n", address, ram[address]);
    }
  }
  else {
    for(int address = 0; address < RAM_SIZE; address++) {
      fprintf(stdout, "Address: %.4d Data: %d\n", address, ram[address]);
    }
  }
}

void Memory::processRequest(std::string request) {
  //Tokenize the input
  char requestCopy[512];
  strncpy(requestCopy, request.c_str(), 512);
  char *token = strtok(requestCopy, " ,()\n");

  //If we received a request to exit
  if(strcmp(token, "EXIT") == 0) {
    releaseMemory = true;
    dataBus->write("EXIT");
  }
  //If we receive a request to query the amount of ram
  else if(strcmp(token, "SIZE") == 0) {
    char size[16];
    sprintf(size, "%d", RAM_SIZE);
    dataBus->write(size);
  }
  //If we received a request to read data
  else if(strcmp(token, "read") == 0) {
    //fprintf(stdout, "Read request...");
    char *addressString = strtok(NULL, " ,()\n");
    char address[128];
    sprintf(address, "%d", ram[atoi(addressString)]);
    dataBus->write(address);
    //fprintf(stdout, "Done\n");
  }
  //If we received a request to write data
  else if(strcmp(token, "write") == 0) {
    //Get address from the request
    char *address = strtok(NULL, " ,()\n");
    //Get data from the request
    char *data = strtok(NULL, " ,()\n");
    //Write the data to memory
    write(atoi(address), atoi(data));
    //Respond that the request was a success
    dataBus->write("SUCCESS");
  }
  //If we received a request we don't recognize output
  else {
    fprintf(stderr, "Unknown Request: %s\n", request.c_str());
  }
}
