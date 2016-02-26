//Daniel Eisterhold
//CS4348 Project 1
//20 Sept. 2015

#ifndef __BUS__
#define __BUS__

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>

#include "FIFO.h"

class BUS {
 public:
  BUS();
  ~BUS();
  std::string read(char terminator = '\n');
  void write(std::string data, const char terminator = '\n');
 private:
  bool firstReadWrite;
  int masterPipe[2];
  int slavePipe[2];
  int readPipe();
  int writePipe(const char data[], int length);
  void update();
  FIFO *buffer;
};

#endif
