//Daniel Eisterhold
//CS4348 Project 1
//17 Sept. 2015

#ifndef __MEMORY__
#define __MEMORY__

#include <stdio.h>
#include <stdlib.h>
#include <string>

#include "BUS.h"
#include "MemoryLoader.h"

#define RAM_SIZE 2000

class Memory {
 public:
  Memory();
  ~Memory();
  void setBus(BUS *bus);
  void load(std::string fileLocation);
  void start();
  void dump(bool hex = false);
 private:
  //Flag to know when to exit
  bool releaseMemory;
  //Data Bus
  BUS *dataBus;
  //Memory as an array
  int ram[RAM_SIZE];
  //Read and Write to Memory
  int read(int address);
  void write(int address, int data);
  //Process a request from the CPU
  void processRequest(std::string request);
};

#endif
