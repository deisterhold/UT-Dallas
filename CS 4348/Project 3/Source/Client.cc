//Daniel Eisterhold
//CS4348 Project 3
//15 November 2015

#include "Client.h"

// MARK: Constructor and Destructor
Client::Client() {

}

Client::~Client() {

}

// MARK: Public Methods
void Client::start(string hostnameOfServer, uint16_t numberOfPort) {
  // Output status of client
  cout<<"Client is connecting to host: "<< hostnameOfServer<<" on port "<<numberOfPort<<endl;

  // Open socket
  socketFD = socket(AF_INET, SOCK_STREAM, 0);

  // Check if socket opened correctly
  if(socketFD < 0) {
    cerr<<"Error opening socket"<<endl;
    exit(1);
  }

  // Get information about host
  hostInfo = gethostbyname(hostnameOfServer.c_str());
  if(hostInfo == 0) {
    cerr<<"Error getting information about host"<<endl;
    exit(1);
  }

  memset(&clientInfo, 0, sizeof(clientInfo));
  clientInfo.sin_family = AF_INET;
  clientInfo.sin_addr.s_addr = ((struct in_addr *)(hostInfo->h_addr))->s_addr;
  clientInfo.sin_port = htons(numberOfPort);

  if(connect(socketFD,(struct sockaddr*) &clientInfo, sizeof(clientInfo)) == -1) {
    cerr<<"Error connecting to server"<<endl;
    exit(1);
  }

  cout<<"Successfully connected to server"<<endl;

  // Variable to hold user input
  int choice;

  // Loop until the user chooses to exit
  do {
    choice = presentMenuToUser();
    processMenuChoice(choice);
  }
  while(choice != 5);

  // Tell the server the client is exiting
  char data[5] = {0,0,0,0,EXIT};
  if(write(socketFD, data, 5) != 5) {
    cerr<<"Error sending exit command to server"<<endl;
  }

  close(socketFD);
}

// MARK: Private Methods
void Client::processMenuChoice(int choice) {
  // Determine what to do based on user input
  switch(choice) {
  case 1:
    listFiles();
    break;
  case 2:
    cout<<"Uploading file to server"<<endl;
    uploadFile();
    break;
  case 3:
    cout<<"Downloading file from server"<<endl;
    downloadFile();
    break;
  case 4:
    cout<<"Deleting file from server"<<endl;
    deleteFile();
    break;
  case 5:
    cout<<"Exiting"<<endl;
    break;
  default:
    cerr<<"Unrecognized menu choice given"<<endl;
  }
}

int Client::presentMenuToUser() {
  // Variable to hold menu choice of user
  int userSelection;

  // Variable to known if the user entered invalid data
  bool invalidInput = false;

  // Display menu to user and read until valid data has been entered
  do {
    // If invalid data was read
    if(invalidInput) {
      // Clear cin and read until a newline
      cin.clear();
      cin.ignore(1000, '\n');
      cerr<<"Invalid input. Choose a value between 1-5 inclusive"<<endl;
    }
    else {
      // Toggle flag
      invalidInput = true;
    }
    // Insert some space before the menu
    cout<<endl<<endl;
    cout<<"-------------File Menu-------------"<<endl;
    cout<<"Please select a menu choice: "<<endl;
    cout<<"1. Display files on server"<<endl;
    cout<<"2. Upload file to server"<<endl;
    cout<<"3. Download file from server"<<endl;
    cout<<"4. Delete file from server"<<endl;
    cout<<"5. Exit"<<endl;
    cout<<"Please select a menu choice: ";

    //Read integer from stdin
    cin>>userSelection;
  }
  while(userSelection > 5 || userSelection <= 0);

  // Insert some space after the menu
  cout<<endl<<endl;

  return userSelection;
}

void Client::listFiles() {
  uint8_t data[5] = {0,0,0,0,GET_FILELIST};
  int length = write(socketFD, data, 5);
  if(length != 5) {
    cerr<<"Error sending data to server"<<endl;
  }
  // Clear array
  memset(data, 0, 5);
  
  // Read data from server
  length = read(socketFD, data, 5);
  
  // Check data from server
  if(length != 5 && data[4] == POST_FILELIST) {
    cerr<<"Error reading data from server"<<endl;
  }

  // Convert data from server
  uint32_t dataLength = 0;
  uint8_t* dataBuffer;
  dataLength += data[0] << 24;
  dataLength += data[1] << 16;
  dataLength += data[2] << 8;
  dataLength += data[3];

  // Allocate memory
  dataBuffer = (uint8_t*) malloc(dataLength);

  // Read data from server
  length = read(socketFD, dataBuffer, dataLength);

  // Check data from server
  if(length != (int) dataLength) {
    cerr<<"Data read from server does not equal expected length of "<<dataLength<<" bytes"<<endl;
  }

  // Variable for holding data returned from server
  vector<string> files;
  string tempString;
  
  // Process data returned from server
  for(uint32_t index = 0; index < dataLength; index++) {
    if(dataBuffer[index] == '\n') {
      files.push_back(tempString);
      tempString = "";
    }
    else {
      tempString += (char) dataBuffer[index];
    }
  }

  cout<<"----------Files:----------"<<endl;
  for(uint index = 0; index < files.size(); index++) {
    cout<<files[index]<<endl;
  }
  cout<<"--------------------------"<<endl;

  // Release memory
  free(dataBuffer);
}

void Client::uploadFile() {
  // Request filename from user
  string filename = getFilename(true);
  ifstream file(filename.c_str());
  uint8_t command[5];
  uint8_t* data;

  // Append newline to string indicating end of filename
  filename += '\n';

  // Calculate file size
  uint32_t fileSize = 0;
  string theStuff;
  string tempString;
  while(getline(file, tempString)) {
    theStuff += tempString;
    tempString = "";
  }

  //  struct stat fileInfo;
  //if(stat(filename.substr(0,filename.length()-1).c_str(), &fileInfo) == 0) {
  //fileSize = fileInfo.st_size;
  //}

  //Calculate data size
  uint32_t dataLength = filename.length() + theStuff.length();

  // Allocate memory
  data = (uint8_t*) malloc(dataLength);

  // Move filename and data into buffer
  uint32_t index = 0;
  for(; index < filename.length(); index++) {
    data[index] = filename[index];
  }
  
  // Copy data from file into buffer  
  for(int letter = 0; index < fileSize; index++, letter++) {
    
    //file>>stuff;
    cout<<"Loading \""<<theStuff[letter]<<"\" into buffer"<<endl;
    data[index] = theStuff[letter];
  }
  

  // Create command to send to server
  command[0] = dataLength & 0xFF000000;
  command[1] = dataLength & 0x00FF0000;
  command[2] = dataLength & 0x000000FF;
  command[3] = dataLength & 0x000000FF;
  command[4] = POST_FILE;

  // Send command to server
  if(write(socketFD, command, 5) != 5) {
    cerr<<"Error sending command to server"<<endl;
  }

  // Send data to server
  if(write(socketFD, data, dataLength) != (int) dataLength) {
    cerr<<"Error sending data to server"<<endl;
  }

  // Release memory
  free(data);
}

void Client::downloadFile() {
  // Request filename from user
  string filename = getFilename();
  ofstream outfile(filename.c_str());
  uint8_t command[5];

  // Append newline to string indicating end of filename
  filename += '\n';

  // Create command to send to server
  uint32_t filenameLength = filename.length();
  command[0] = filenameLength & 0xFF000000;
  command[1] = filenameLength & 0x00FF0000;
  command[2] = filenameLength & 0x000000FF;
  command[3] = filenameLength & 0x000000FF;
  command[4] = GET_FILE;

  // Send command to server
  if(write(socketFD, command, 5) != 5) {
    cerr<<"Error sending command to server"<<endl;
  }

  // Send data to server
  if(write(socketFD, filename.c_str(), filename.length()) != (int) filename.length()) {
    cerr<<"Error sending data to server"<<endl;
  }

  // Clear command array
  memset(command, 0, 5);

  // Read command from server
  if(read(socketFD, command, 5) != 5) {
    cerr<<"Incorrect command length received from server"<<endl;
  }

  // Calculate size of data
  uint32_t dataSize = 0;
  dataSize |= command[0] & 0xFF000000;
  dataSize |= command[1] & 0x00FF0000;
  dataSize |= command[2] & 0x0000FF00;
  dataSize |= command[3] & 0x000000FF;

  // Buffer for data from server
  uint8_t* dataBuffer = (uint8_t*) malloc(dataSize);

  // Read data from server
  if(read(socketFD, dataBuffer, dataSize) != (int) dataSize) {
    cerr<<"Incorrect data length received from server"<<endl;
  }

  // Loop through array and store into file
  cout<<"Writing data to file"<<endl;
  for(uint32_t index = 0; index < dataSize; index++) {
    char stuff = dataBuffer[index];
    outfile << stuff;
  }

  cout<<"Done writing to file"<<endl;

  // Close file
  outfile.close();

  // Release memory
  free(dataBuffer);
}

void Client::deleteFile() {
  // Request filename from user
  string filename = getFilename();
  uint8_t command[5];

  // Append newline to string indicating end of filename
  filename += '\n';

  // Create command to send to server
  uint32_t filenameLength = filename.length();
  command[0] = filenameLength & 0xFF000000;
  command[1] = filenameLength & 0x00FF0000;
  command[2] = filenameLength & 0x000000FF;
  command[3] = filenameLength & 0x000000FF;
  command[4] = DELETE_FILE;

  // Send command to server
  if(write(socketFD, command, 5) != 5) {
    cerr<<"Error sending command to server"<<endl;
  }

  // Send data to server
  if(write(socketFD, filename.c_str(), filename.length()) != (int) filename.length()) {
    cerr<<"Error sending data to server"<<endl;
  }
}

string Client::getFilename(bool localFile) {
  bool invalidInput = false;
  bool validFilename = false;
  string filename;
  
  do {
    if(invalidInput) {
      cerr<<"Invalid filename. Ex. \"myfile.txt\""<<endl;
      cin.clear();
      cin.ignore(1000, '\n');
    }
    else {
      invalidInput = true;
    }
    cout<<"Please type the filename followed by enter: ";
    cin>>filename;

   // Make sure the filename is long enough ("x.xxx")
   if(filename.length() > 5) {
      // Check to see that there is a period on the fourth to last character
      if(filename[filename.length()-4] == '.') {
	// If the file needs to be on the local filesystem (Ex. for uploading)
	if(localFile) {
	  // Variable to hold file stream
	  ifstream input;
	  
	  // Attempt to open the file
	  input.open(filename.c_str());

	  // See if the file could be opened
	  if(input.is_open()) {
	    // Flip flag indicating filename is valid
	    validFilename = true;
	  }

	  // Close file
	  input.close();
	}
	else {
	  // Flip flag indicating filename is valid  
	  validFilename = true;
	}
      }
    }
  }
  while(!validFilename);

  return filename;
}
