//Daniel Eisterhold
//CS4348 Project 3
//15 November 2015

#include "Server.h"

// MARK: Static Property Initialization
vector<pthread_t> Server::serverThreads = vector<pthread_t>();

// MARK: Constructor and Destructor
Server::Server() {
  // Initialize thread attributes
  pthread_attr_init(&threadAttributes);
  
  // Set the thread to be a detachable thread
  pthread_attr_setdetachstate(&threadAttributes, PTHREAD_CREATE_DETACHED);
}

Server::~Server() {
  // Destroy thread attributes
  pthread_attr_destroy(&threadAttributes);
}

// MARK: Public Methods
void Server::start(uint16_t numberOfPort) {
  FileManager::get()->create("test1.txt");
  FileManager::get()->create("test2.txt");

  vector<uint8_t>* file1 = FileManager::get()->startEditing("test1.txt");
  vector<uint8_t>* file2 = FileManager::get()->startEditing("test2.txt");

  string test1 = "Hello!, World!";
  string test2 = "1,2,3,4,5,6,7,8,9,0";

  for(uint letter = 0; letter < test1.length(); letter++) {
    file1->push_back(test1[letter]);
  }

  for(uint letter = 0; letter < test2.length(); letter++) {
    file2->push_back(test2[letter]);
  }

  FileManager::get()->stopEditing("test1.txt");
  FileManager::get()->stopEditing("test2.txt");

  char hostName[256];
  if(gethostname(hostName, sizeof(hostName)) == -1) {
    cerr<<"Error getting hostname"<<endl;
    exit(1);
  }
  cout<<"Server running on host: "<<hostName<<" at port: "<<numberOfPort<<endl;

  // Initialize socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0);
  
  // Check if call returned a valid file descriptor
  if(socketFD < 0) {
    cerr<<"Error opening socket"<<endl;
    exit(1);
  }
  
  // Initialize server info struct
  memset(&serverInfo, 0, sizeof(serverInfo));
  serverInfo.sin_family = AF_INET;
  serverInfo.sin_addr.s_addr = INADDR_ANY;
  serverInfo.sin_port = htons(numberOfPort);

  if(bind(socketFD, (struct sockaddr*) &serverInfo, sizeof(serverInfo)) < 0) {
    cerr<<"Error binding socket to server"<<endl;
    exit(1);
  }
  
  // Start listening for clients
  listen(socketFD, MAX_NUMCLIENTS);

  // Block until a client connects
  while(true) {
    struct sockaddr_in clientInfo;
    socklen_t len = sizeof(clientInfo);
    pthread_t clientThread;

    // Accept connection from client
    int clientFD = accept(socketFD, (sockaddr*) &clientInfo, &len);

    // Check to see if connection was opened properly
    if(clientFD < 0) {
      cerr<<"Error opening connection to client"<<endl;
      exit(1);
    }
    else {
      // Allocate memory
      int* clientStuff = (int*) malloc(sizeof(clientFD));
      
      // Set pointer value to the file descriptor
      *clientStuff = clientFD;
      
      // Create a thread to handle the client and pass it the client's file descriptor
      pthread_create(&clientThread, &threadAttributes, handleClient, clientStuff);
    }
  }
  cout<<"Server exiting"<<endl;
  // Close the socket
  close(socketFD);

  return;
}

void* Server::handleClient(void* clientFD) {
  // Flag to know when to exit the thread
  bool exitThread = false;

  // Convert the void pointer to an integer
  int fd = *((int *) clientFD);

  // Release memory
  free(clientFD);

  // Get a reference to the file manager
  FileManager* manager = FileManager::get();

  // Loop until the connection has stopped
  while(!exitThread) {
    // Array to hold payload size and command (4 + 1 bytes)
    uint8_t rxCommandBuffer[5];
    // Array to hold data
    uint8_t* rxDataBuffer;
    // Length of data from client
    uint32_t rxDataBufferSize = 0;

    
    // Read data from client
    if(read(fd, rxCommandBuffer, 5) < 0) {
      cerr<<"Error reading data from client"<<endl;
      exit(1);
    }

    // Convert bytes to 32 bit unsigned integer
    rxDataBufferSize |= rxCommandBuffer[0] & 0xFF000000;
    rxDataBufferSize |= rxCommandBuffer[1] & 0x00FF0000;
    rxDataBufferSize |= rxCommandBuffer[2] & 0x0000FF00;
    rxDataBufferSize |= rxCommandBuffer[3] & 0x000000FF;

    // Allocate memory
    rxDataBuffer = (uint8_t*) malloc(rxDataBufferSize);

    // Read rest of the data from the pipe
    int bytesRead;
    if((bytesRead = read(fd, rxDataBuffer, rxDataBufferSize)) != (int) rxDataBufferSize) {
      cerr<<"Data read from socket is incorrect length"<<endl;
      cerr<<"Read "<<bytesRead<<" bytes, but should have read "<<rxDataBufferSize<<" bytes"<<endl;
    }

    
    uint8_t txCommandBuffer[5];
    uint8_t* txDataBuffer;
    uint32_t txDataBufferSize = 0;

    switch(rxCommandBuffer[4]) {
    case GET_FILELIST: {
      // Get a list of the files in the file manager
      vector<string> fileList = manager->listOfFiles();

      cout<<"Retrieving file list and sending to client"<<endl;
      if(rxDataBufferSize > 0) {
	cerr<<"Payload size should be zero for this request"<<endl;
      }

      // Create a string to hold the list of files
      string dataString;
      // File the string with the list of files and each name followed by a newline
      for(uint index = 0; index < fileList.size(); index++) {
	dataString += fileList[index];
	dataString += '\n';
      }
      
      //Put length and command into array
      txCommandBuffer[0] = dataString.length() & 0xFF000000;
      txCommandBuffer[1] = dataString.length() & 0x00FF0000;
      txCommandBuffer[2] = dataString.length() & 0x0000FF00;
      txCommandBuffer[3] = dataString.length() & 0x000000FF;
      txCommandBuffer[4] = POST_FILELIST;

      // Send command to client
      if(write(fd, txCommandBuffer, 5) != 5) {
	cerr<<"Error sending command to client"<<endl;
      }

      // Send data to client
      if(write(fd, dataString.c_str(), dataString.length()) != (int) dataString.length()) {
	cerr<<"Error sending data to client"<<endl;
      }

      break;
    }
    case GET_FILE: {
      // Variable to hold the name of the file to retrieve
      string filename;
      // Variable to hold the file to send
      vector<uint8_t>* fileToSend;

      // Loop through the data and get the file name
      for(uint32_t index = 0; index < rxDataBufferSize; index++) {
	// If a newline is encountered exit the loop
	if(rxDataBuffer[index] == '\n') {
	  break;
	}
	else {
	  // Append the data to the file name
	  filename += (char) rxDataBuffer[index];
	}
      }

      cout<<"Sending file: "<<filename<<", ...";

      // Get the file that is supposed to be sent and lock mutex on file
      fileToSend = manager->startEditing(filename);

      // Allocate memory in the data buffer
      txDataBuffer = (uint8_t*) malloc(fileToSend->size());
      txDataBufferSize = (uint32_t) fileToSend->size();

      txCommandBuffer[0] = txDataBufferSize & 0xFF000000;
      txCommandBuffer[1] = txDataBufferSize & 0x00FF0000;
      txCommandBuffer[2] = txDataBufferSize & 0x0000FF00;
      txCommandBuffer[3] = txDataBufferSize & 0x000000FF;
      txCommandBuffer[4] = POST_FILE;

      // Move file into tx buffer
      for(uint32_t pos = 0; pos < txDataBufferSize; pos++) {
	txDataBuffer[pos] = (*fileToSend)[pos];
      }

      // Send command
      if(write(fd, txCommandBuffer, 5) != 5) {
	cerr<<"Error sending response to client"<<endl;
      }

      // Send data
      if(write(fd, txDataBuffer, txDataBufferSize) != (int) txDataBufferSize) {
	cerr<<"Error sending file: "<<filename<<"to client."<<endl;
      }

      // Unlock mutex on file
      manager->stopEditing(filename);

      // Release memory
      free(txDataBuffer);

      cout<<"Done"<<endl;
      break;
    }
    case POST_FILE: {
      // Variable to hold the name of the file to retrieve                                          
      string filename;
      // Variable to hold the file to receive
      vector<uint8_t>* fileToReceive;

      // Loop through the data and get the file name                                                
      uint32_t index = 0;
      for(; index < rxDataBufferSize; index++) {
        // If a newline is encountered exit the loop                                                
        if(rxDataBuffer[index] == '\n') {
          break;
        }
        else {
          // Append the char to the file name                                                       
          filename += (char) rxDataBuffer[index];
        }
      }

      // If the file exists
      if(manager->exists(filename)) {
	// Open the file
	fileToReceive = manager->startEditing(filename);
      }
      else {
	// Create a new file
	manager->create(filename);
	// Open newly created file
	fileToReceive = manager->startEditing(filename);
      }

      cout<<"Receiving file: "<<filename<<", ...";

      //Erase the contents of the file
      fileToReceive->erase(fileToReceive->begin(),fileToReceive->end());
      cout<<"Erasing previous file, size: "<<fileToReceive->size()<<endl;

      // Append the new data to the file
      for(; index < rxDataBufferSize; index++) {
	char letter = rxDataBuffer[index];
	cout<<"Storing \""<<letter<<"\" into file manager"<<endl;
	fileToReceive->push_back(letter);
      }

      manager->stopEditing(filename);
      cout<<"Done"<<endl;

      break;
    }
    case DELETE_FILE: {
      // Variable to hold the name of the file to retrieve                                                        
      string filename;

      // Loop through the data and get the file name                                                              
      for(uint32_t index = 0; index < rxDataBufferSize; index++) {
        // If a newline is encountered exit the loop                                                              
        if(rxDataBuffer[index] == '\n') {
          break;
        }
        else {
          // Append the data to the file name                                                                     
          filename += (char) rxDataBuffer[index];
        }
      }
      cout<<"Deleting file: "<<filename<<endl;
      FileManager::get()->destroy(filename);
      break;
    }
    case EXIT: {
      cout<<"Thread exiting"<<endl;
      exitThread = true;
      break;
    }
    default: {
      cerr<<"Invalid request received from client. Terminating"<<endl;
    }
    }
    // Release memory                                                                             
    free(rxDataBuffer);
  }
  
  return NULL;
}
