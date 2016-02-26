//Daniel Eisterhold
//dte130030@utdallas.edu
//CS4381.001

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>
#include <iostream>

#include "CPU.h"
#include "Memory.h"

using namespace std;

pid_t processID;

#define FILE_LOCATION "/Users/deisterhold/Google Drive/College/Fall 2015/CS 4348/Projects/Project 1/Project_1/samples/sample4.txt"

void handleSignal(int num) {
  exit(1);
}

int main(int argc, char* argv[]) {
  //Create an instance of bus to communicate between CPU and RAM
  BUS *dataBus = new BUS();

  processID = fork();

  if(processID < 0) {
    fprintf(stderr, "Error forking.\n");
    exit(1);
  }
  else if(processID == 0) {
    signal(SIGINT, handleSignal);
    //Create CPU
    CPU *cpu1 = new CPU();
    if(cpu1 == NULL) cerr<<"Error initializing CPU"<<endl;
    //Set data bus of CPU
    cpu1->setBus(dataBus);
    //Start CPU and pass timer value
    cpu1->start();
  }
  else if(processID > 0) {
    signal(SIGINT, handleSignal);
    //Create RAM
    Memory *ram = new Memory();
    if(ram == NULL) cerr<<"Error initializing Memory"<<endl;
    //Set data bus
    ram->setBus(dataBus);
    //Set file to read from
    ram->load(FILE_LOCATION);
    //Start memory
    ram->start();
  }

  return 0;
}
