//Daniel Eisterhold
//CS4348 Project 1
//28 Sept. 2015

#ifndef __MEMORY_LOADER__
#define __MEMORY_LOADER__

#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <cstring>
#include <string>

class MemoryLoader {
 public:
  MemoryLoader();
  MemoryLoader(std::string pathToFile);
  ~MemoryLoader();
  bool setFilePath(std::string pathToFile);
  void startParsing(int *ram, size_t size);
 private:
  std::string path;
  std::ifstream inputFile;
  int currentAddress;
  void parseLine(char *cstring, int *ram, size_t size);
};

#endif
