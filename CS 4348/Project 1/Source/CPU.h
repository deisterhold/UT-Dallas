//Daniel Eisterhold
//CS4348 Project 1
//17 Sept. 2015

#ifndef __CPU__
#define __CPU__

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string>

#include "BUS.h"

class CPU {
 public:
  CPU();
  ~CPU();
  void setBus(BUS *bus);
  void start(unsigned int timerValue = 0);
 private:
  //Flag to know when to exit
  bool exitInstructionExecuted;
  //Flag to know whether to execute as user or kernel
  bool kernelMode;
  //Data Bus
  BUS *dataBus;
  //Registers
  int _pc, _sp, _ir, _ac, _x, _y;
  //Pointers to the stack
  int sysP, usrP;
  //Flag to know whether it is a timer interrupt or normal interrupt
  bool timerInterrupt;
  //Function to initialize memory and deinitialize when done executing instructions
  void initializeMemory();
  void deinitializeMemory();
  //Functions for accessing memory and executing instructions
  void executeInstruction();
  int readMemory(int address);
  bool writeMemory(int address, int data);
};

#endif
