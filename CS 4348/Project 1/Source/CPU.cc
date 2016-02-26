//Daniel Eisterhold
//CS4348 Project 1
//17 Sept. 2015

#include "CPU.h"

CPU::CPU() {
  //Set the exit flag to false (disabled)
  exitInstructionExecuted = false;

  //Set mode to user mode by default
  kernelMode = false;

  //Set program counter to start of memory
  _pc = 0;
  
  //Set stack pointers
  sysP = 1999;
  usrP = 999;
  _sp = usrP;

  //Set default interrupt
  timerInterrupt = false;

  //Initialize random number generator
  srand(time(0));
}

CPU::~CPU() {
}

void CPU::setBus(BUS *bus) {
  dataBus = bus;
}

void CPU::initializeMemory() {
  //Send a request to see if the memory is initialized and loaded
  dataBus->write("READY");
  
  //Store the response from the request
  std::string response = dataBus->read();

  //If we did not receive the correct response print an error
  if(response != "READY") {
    fprintf(stderr, "Error checking if memory is ready.\n");
  }
}

void CPU::deinitializeMemory() {
  //Send an exit request to memory
  dataBus->write("EXIT");
  
  //Store the response from the request
  std::string response = dataBus->read();

  //If we did not receive the correct response print an error
  if(response != "EXIT") {
    fprintf(stderr, "Error telling memory to exit.\n");
  }
}

int CPU::readMemory(int address) {
  //Buffer to hold the request we are making
  char buffer[64];

  //Format the request and store it in the buffer
  sprintf(buffer, "read(%d)", address);

  //Send the request to memory
  dataBus->write(std::string(buffer));

  //Store the response from the request
  std::string data = dataBus->read();

  //Convert the response to an integer and return
  return atoi(data.c_str());
}

bool CPU::writeMemory(int address, int data) {
  //Buffer to hold the request we are making
  char buffer[64];

  //Format the request and store it in the buffer
  sprintf(buffer, "write(%d,%d)", address, data);
  
  //Send the request
  dataBus->write(std::string(buffer));
  
  //Read the response from the request
  std::string response = dataBus->read();
  
  //If the request was successful return true
  if(response == "SUCCESS") {
    return true;
  }
  //Otherwise return false
  else {
    fprintf(stderr, "Attempt to write to memory failed\n");
    return false;
  }
}

void CPU::start(unsigned int timerValue) {
  //Check that the memory is ready
  initializeMemory();
  
  int numInstructions = 0;

  //Loop until the exit flag has been flipped
  while(!exitInstructionExecuted) {
    //Read instruction from memory
    _ir = readMemory(_pc);
    //Increment program counter
    _pc++;
    //Execute the instruction
    executeInstruction();
    //Counter for timer
    numInstructions++;
    if((numInstructions == timerValue) && (timerValue > 0)) {
      numInstructions = 0;
    }
    usleep(1000);
  }

  //Tell the memory to exit
  deinitializeMemory();
}

void CPU::executeInstruction() {
  //Execute the instruction
  switch(_ir) {
  case 1: {
    //Load value at the address into register
    _ac = readMemory(_pc);
    _pc++;
    break;
  }
  case 2: {
    //Load the address from memory
    int address = readMemory(_pc);
    _pc++;
    //Load the value at the address from memory
    _ac = readMemory(address);
    break;
  }
  case 3: {
    //Load the first address from memory
    int address1 = readMemory(_pc);
    _pc++;
    int address2 = readMemory(address1);
    _ac = readMemory(address2);
    break;
  }
  case 4: {
    //Load the address from memory
    int address = readMemory(_pc);
    _pc++;
    //Read address plus offset from x into ac
    _ac = readMemory(address + _x);
    break;
  }  
  case 5: {
    //Load the address from memory
    int address = readMemory(_pc);
    _pc++;
    //Store the address plus offset from y into ac
    _ac = address + _y;
    break;
  }
  case 6: {
    //Load data from sp with offset x into ac
    _ac = readMemory(_sp + _x);
    break;
  }
  case 7: {
    //Get address from memory
    int address = readMemory(_pc);
    _pc++;
    //Write value from ac into memory
    writeMemory(address, _ac);
    break;
  }    
  case 8: {
    //Get random number between 1-100 and store into ac
    _ac = (rand() % 100) + 1;
    break;
  }
  case 9: {
    //Read port from memory
    int port = readMemory(_pc);
    _pc++;
    //If port is 1 write as an integer
    if(port == 1) {
      fprintf(stdout, "%d", _ac);
    }
    //If port is 2 write as a char
    else if(port == 2) {
      fprintf(stdout, "%c", _ac);
    }
    break;
  }
  case 10: {
    //Add value in x to ac
    _ac += _x;
    break;
  }
  case 11: {
    //Add value in y to ac
    _ac += _y;
    break;
  }
  case 12: {
    //Subtract value in x from ac
    _ac -= _x;
    break;
  }
  case 13: {
    //Subtract value in y from ac
    _ac -= _y;
    break;
  }
  case 14: {
    //Copy ac to x
    _x = _ac;
    break;
  }
  case 15: {
    //Copy x to ac
    _ac = _x;
    break;
  }
  case 16: {
    //Copy ac to y
    _y =  _ac;
    break;
  }
  case 17: {
    //Copy y to ac
    _ac = _y;
    break;
  }
  case 18: {
    //Copy ac to sp
    _sp = _ac;
    break;
  }
  case 19: {
    //Copy sp to ac
    _ac = _sp;
    break;
  } 
  case 20: {
    //Jump to address
    _pc = readMemory(_pc);
    break;
  }
  case 21: {
    //If ac is zero
    if(_ac == 0) {
      //Jump to address
      _pc = readMemory(_pc);
    }
    break;
  }
  case 22: {
    //If ac is not zero
    if(_ac != 0) {
      //Jump to address
      _pc = readMemory(_pc);
    }
    break;
  }
  case 23: {
    //Read address from memory
    int address = readMemory(_pc);
    _pc++;
    //Save program counter onto stack
    writeMemory(_sp, _pc);
    //Decrement stack pointer
    _sp--;
    //Jump to address read off stack pointer
    _pc = address;
    break;
  }
  case 24: {
    //Increment stack pointer
    _sp++;
    //Get address from stack
    int address = readMemory(_sp);
    //Set program counter to address
    _pc = address;
    break;
  }
  case 25: {
    //Increment x
    _x++;
    break;
  }
  case 26: {
    //Decrement x
    _x--;
    break;
  }
  case 27: {
    //Push ac onto stack
    writeMemory(_sp, _ac);
    //Decrement stack pointer
    _sp--;
    break;
  }
  case 28: {
    //Pop ac from stack
    _ac = readMemory(_sp);
    //Increment stack pointer
    _sp++;
    break;
  }
  case 29: {
    //Set to kernel mode
    kernelMode = true;

    //Write stack pointer to user stack
    writeMemory(_sp, _sp);
    //Decrement stack pointer
    _sp--;
    //Write program counter to user stack
    writeMemory(_sp, _pc);
    //Decrement stack pointer
    _sp--;
    //Set user point to current stack pointer
    usrP = _sp;

    //Set the stack pointer to the current system pointer
    _sp = sysP;
    if(timerInterrupt) {
      _pc = 1000;
    }
    else {
      _pc = 1000;
    }
    
    //Set stack pointer to system stack pointer
    _sp = sysP;
    break;
  }
  case 30: {
    //Save stack pointer to system pointer
    sysP = _sp;
    //Restore user point to stack pointer
    _sp = usrP;
    //Read stack pointer
    _sp = readMemory(_sp);
    _sp++;
    _pc = readMemory(_sp);
    _sp++;
    //Set to user mode
    kernelMode = false;
    break;
  }
  case 50: {
    exitInstructionExecuted = true;
    break;
  }
  default:
    fprintf(stderr, "Error: Unrecognized Instruction: %d\n", _ir);
  }
  //usleep(10000);
}
