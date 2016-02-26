//Daniel Eisterhold
//CS4348 Project 1
//21 Sept. 2015

#include "BUS.h"

extern pid_t processID;

BUS::BUS() {
  //Create pipe for sending data to master
  pipe(masterPipe);
  //Create pipe for sending data to slace
  pipe(slavePipe);
  //Flag indicating that either the first read or write has occurred
  firstReadWrite = false;
  //Initialize FIFO buffer
  buffer = new FIFO();
}

BUS::~BUS(){
  if(processID == 0) {
    //Child
    //Close input of the master pipe
    close(masterPipe[1]);
    //Close output of the slave pipe
    close(slavePipe[0]);
    //If the first read or write hasn't occurred
    if(!firstReadWrite) {
      //Close output of the master pipe
      close(masterPipe[0]);
      //Close input of the slave pipe
      close(slavePipe[1]);
    }
  }
  else {
    //Parent                        
    //Close output of the master pipe
    close(masterPipe[0]);
    //Close input of the slave pipe
    close(slavePipe[1]);
    //If the first read or write hasn't occurred
    if(!firstReadWrite) {
      //Close input of the master pipe
      close(masterPipe[1]);
      //Close output of the slave pipe
      close(slavePipe[0]);
    }
  }
}

int BUS::readPipe() {
  //Buffer to hold data from pipe
  char tempBuffer[512];
  //Var to hold the amount of data read
  int size = 0;
  //Read from either the parent or child pipe
  if(processID == 0) {
    //Child
    //If the first read or write hasn't occurred
    if(!firstReadWrite) {
      //Set the flag indicating the first read or write has occurred
      firstReadWrite = true;
      //Close output of the master pipe
      close(masterPipe[0]);
      //Close input of the slave pipe
      close(slavePipe[1]);
    }
    //Read char from the slave pipe and return it
    size = ::read(slavePipe[0], tempBuffer, sizeof(tempBuffer)/sizeof(tempBuffer[0]));
    //fprintf(stdout, "Child read %d bytes from the pipe\n", size);
  }
  else {
    //Parent
    if(!firstReadWrite) {
      //Set the flag indicating the first read or write has occurred
      firstReadWrite = true;
      //Close the input of the master pipe
      close(masterPipe[1]);
      //Close the output of the slave pipe
      close(slavePipe[0]);
    }
    //Read data from the master pipe and return the number of characters read
    size = ::read(masterPipe[0], tempBuffer, sizeof(tempBuffer)/sizeof(tempBuffer[0]));
    //fprintf(stdout, "Parent read %d bytes from the pipe\n", size);
  }

  if(size < 0) {
    fprintf(stderr, "Error reading from pipe. No data read.\n");
    fprintf(stderr, "Error code: %d\n", size);
    perror("Pipe Read");
    fprintf(stderr, "\n");
  }

  //Copy data from array to FIFO buffer
  for(int index = 0; index < size; index++) {
    buffer->push(tempBuffer[index]);
  }

  //Return the amount of data read
  return size;
}

int BUS::writePipe(const char data[], int length) {
  //Variable to hold the size of the data written to the pipe
  int size = 0;
  if(processID == 0) {
    //Child            
    //If the first read or write hasn't occurred
    if(!firstReadWrite) {
      //Set the flag indicating the first read or write has occurred                                     
      firstReadWrite = true;
      //Close output of the master pipe                                                                  
      close(masterPipe[0]);
      //Close input of the slave pipe                                                                    
      close(slavePipe[1]);
    }
    //Write data to the master pipe and return the number of characters written
    size = ::write(masterPipe[1], data, length);
    //fprintf(stdout, "Child sent %d bytes to master\n", size);
  }
  else {
    //Parent                                                                                             
    if(!firstReadWrite) {
      //Set the flag indicating the first read or write has occurred                                     
      firstReadWrite = true;
      //Close the input of the master pipe                                                               
      close(masterPipe[1]);
      //Close the output of the slave pipe                                                               
      close(slavePipe[0]);
    }
    //Write data to the slave pipe and return the number of characters written
    size = ::write(slavePipe[1], data, length);
    //fprintf(stdout, "Parent sent %d bytes to slave\n", size);
  }
  //Return the number of bytes written
  return size;
}

std::string BUS::read(char terminator) {
  //Variable to hold request
  std::string data = "";

  //If the buffer is empty
  if(buffer->size() == 0) {
    //Check the pipe until you get some data
    while(!readPipe()) {
      //Wait a little before checking again
      usleep(1000);
      fprintf(stdout, "Waiting for more data from pipe\n");
    }
  }

  //While we have not reached the terminator
  while(buffer->peek() != terminator) {
    //Append character to string
    data += buffer->pop();
    
    //If there is only one byte or less in the buffer and it isn't the terminator
    if((buffer->size() <= 1) && (buffer->peek() != terminator)) {
      //Check the pipe until you get some data
      while(!readPipe()) {
	//Wait a little before checking again
	usleep(100000);
	fprintf(stdout, "Waiting for more data from pipe\n");
      }
    }
    
    if(buffer->size() == 0) {
      fprintf(stderr, "Buffer is empty, but shouldn't be\n");
      while(1);
      //exit(1);
    }
  }

  //Remove the terminator from the buffer
  buffer->pop();

  if(data.length() == 0) {
    fprintf(stderr, "Error: returning from read with empty command\n");
    exit(1);
  }

  //Return the data
  return data;
}

void BUS::write(std::string data, const char terminator) {
  //Write the string to the pipe
  writePipe(data.c_str(), data.length());
  //Write a terminator to the pipe so we know we have received the end of the command
  writePipe(&terminator, 1);
}
