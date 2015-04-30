//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include <unistd.h>
#include "FileHandler.h"
#include "Logger.h"

#include <cryptopp/default.h>
using CryptoPP::DefaultDecryptor;
using CryptoPP::DefaultEncryptor;

#include <cryptopp/cryptlib.h>
#include <cryptopp/files.h>
using CryptoPP::FileSource;
using CryptoPP::FileSink;

#include <cryptopp/filters.h>

#include <cryptopp/hex.h>
using CryptoPP::HexEncoder;
using CryptoPP::HexDecoder;

#include <fstream>

vector<string> FileHandler::getNamesOfBackups(string relativePath) {
  logger.logVerbose("Getting backup file names for original file: \"" + relativePath + "\"\n");
  vector<string> fileNames;
  string fullCommand = "ls -1 ";
  fullCommand += directory;
  fullCommand += relativePath;
  fullCommand += "*";

  logger.logVerbose("Running command \"" + fullCommand + "\"\n");
  
  FILE *input;
  char buff[1024];
  
  input = popen(fullCommand.c_str(),"r");

  if(input == NULL) {
    logger.logError("Error opening pipe.\n");
    exit(1);
  }

  while(fgets(buff, 1024, input)) {
    string fileName = buff;
    fileNames.push_back(fileName);
  }
  pclose(input);  

  sort(fileNames.begin(),fileNames.end());

  return fileNames;
}

string FileHandler::makeFilename(string fileName) {                                                  logger.logVerbose("Creating file name.\n");
  string command = "date +" + fileName + ".%Y.%m.%d.%H.%M.%S";                                                                        
  FILE *input;                                                                                                                        
  input = popen(command.c_str(), "r");                                                                                                
  if(input == NULL) {                                                                                                                 
    cerr<<"Error creating filename."<<endl;                                                                                           
    pclose(input);                                                                                                                    
    return "";                                                                                                                        
  }                                                                                                                                   
  else {                                                                                                                              
    string newFilename;                                                                                                               
    char buffer[1024];                                                                                                                
    while(fgets(buffer, 1024, input)) {                                                                                               
      newFilename += string(buffer);                                                                                                  
    }                                                                                                                                 
    pclose(input);                                                                                                                    
    return newFilename.substr(0,newFilename.length()-1);
  }                                                                                                                                   
} 

void FileHandler::deleteFile(const string relativePath) {
  logger.logVerbose("Deleting \"" + relativePath + "\"\n");
  string fullCommand = "rm -f ";
  fullCommand += directory;
  fullCommand += relativePath;
  system(fullCommand.c_str());
}

void FileHandler::moveFile(const string fromLocation, const string toLocation) {
  logger.logVerbose("Moving file \"" + fromLocation + "\" to \"" + toLocation + "\" .\n");
  string fullCommand = "mv ";
  fullCommand += fromLocation;
  fullCommand += " ";
  fullCommand += toLocation;
  system(fullCommand.c_str());
}

void FileHandler::copyFile(const string fromLocation, const string toLocation) {
  logger.logVerbose("Copying file \"" + fromLocation + "\" to \"" + toLocation + "\" .\n");
  string fullCommand = "cp ";
  fullCommand += fromLocation;
  fullCommand += " ";
  fullCommand += toLocation;
  system(fullCommand.c_str());
}

void FileHandler::encryptFile(const string fileName, const string password) {
  logger.logVerbose("Creating an encrypted file.\n");
  string inputFile = directory;
  inputFile += fileName;
  string outputFile = directory;
  outputFile += ".secure/";
  outputFile += makeFilename(fileName);
  FileSource input(inputFile.c_str(), true, new DefaultEncryptor(password.c_str(), new HexEncoder( new FileSink(outputFile.c_str()))));
}

void FileHandler::decryptFile(const string fileName, const string password) {
  logger.logVerbose("Creating a decrypted file.\n");
  string inputFile = directory;
  inputFile += ".secure/";
  inputFile += fileName;
  string outputFile = directory;
  outputFile += fileName;
  FileSource input(inputFile.c_str(), true, new HexDecoder( new DefaultDecryptor(password.c_str(), new FileSink(outputFile.c_str()))));
}

bool FileHandler::fileExists(string fileLocation) {
  logger.logVerbose("Checking if file \"" + fileLocation + "\" exists.\n");
  ifstream inputFile(fileLocation.c_str());
  if(!inputFile) {
    logger.logVerbose("File does not exist!\n");
    inputFile.close();
    return false;
  }
  else {
    logger.logVerbose("File exists!\n");
    inputFile.close();
    return true;
  }
}

void FileHandler::makeDirectory(const string folderName) {
  logger.logVerbose("Creating a new directory.\n");
  string fullCommand = "mkdir -p ";
  fullCommand += directory;
  fullCommand += folderName;
  system(fullCommand.c_str());
}

FileHandler::FileHandler() {
  numBackups = 10;
  logFile = directory;
  logFile += "cs3376dirmond.log";
  encryptBackup = false;
}

FileHandler::FileHandler(const string watchDirectory, const string password) {
  directory = watchDirectory;
  numBackups = 10;
  logFile = directory;
  logFile += "cs3376dirmond.log";
  encryptBackup = true;
  makeDirectory(".secure");
  backupPassword = password;
}

FileHandler::FileHandler(const string watchDirectory) {
  directory = watchDirectory;
  numBackups = 10;
  logFile = directory;
  logFile += "cs3376dirmond.log";
  encryptBackup = false;
  makeDirectory(".versions");
}

FileHandler::~FileHandler() {
   if(loggerInitialized) {
    logger.log("Logger stopping.\n");
    logger.stop();
  }
}

void FileHandler::makeBackup(const string fileName) {
  string newFilename = makeFilename(fileName);
  vector<string> backupFilenames;

  if(encryptBackup) {
    logger.logVerbose("Making an encrypted backup\n");
    encryptFile(fileName, backupPassword);
    backupFilenames = getNamesOfBackups(".secure/" + fileName);
  }
  else {
    logger.logVerbose("Making an unencrypted backup\n");
    copyFile(directory + fileName, directory + ".versions/" + newFilename);
    backupFilenames = getNamesOfBackups(".versions/" + fileName);
  }


  logger.log("Files backed up: \n");
  for(int count = 0; count < backupFilenames.size(); count++) {
    logger.log(backupFilenames.back());
    backupFilenames.pop_back();
  }
  
  return;
  //Check for number of versions
  if(backupFilenames.size() > numBackups) {
    logger.logErrorVerbose("Number of files backed up is greater than the quantity set to keep.\n");
    while(backupFilenames.size() > numBackups) {
      deleteFile(backupFilenames.back());
      backupFilenames.pop_back();
      logger.logVerbose("Deleting backup file\n");
    }
  }

}


void FileHandler::setNumBackups(int num) {
  logger.logVerbose("Changing number of backup copies to keep\n");
  
  if(num >= 1) numBackups = num;
}

int FileHandler::getNumBackups() {
  return numBackups;
}

void FileHandler::enableVerbose() {
  logger.log("Verbose Enabdled\n");
  logger.enableVerbose();
}

void FileHandler::disableVerbose() {
  logger.log("Verbose Disabled\n");
  logger.disableVerbose();
}

void FileHandler::setLogFile(const string fileName) {
  logFile = directory;
  logFile += fileName;
  logger.log("Changing log file to: " + fileName + "\n");
  logger.stop();
  logger.setLogFile(logFile);
  logger.start();
}

string FileHandler::getLogFile() {
  return logFile;
}

void FileHandler::start() {

  //Create logger if it hasn't been created
  if(!loggerInitialized) {
    loggerInitialized = true;
    logger.setLogFile(logFile);
    logger.start();
  }

  //Initialize inotify
  logger.logVerbose("Initializing inotify.\n");
  length = 0;
  fd = inotify_init();
  if(fd < 0) {
    logger.logError("Error initializing inotify.\n");
    perror("inotify_init");
  }
  wd = inotify_add_watch(fd, directory.substr(0,directory.length()-1).c_str(),IN_MODIFY);
  
  logger.logVerbose("Inotify initialized.\n");

  /*
  for(int count = 0; count < 10; count++) {
    makeBackup("test.txt");
    sleep(1);
  }
*/
}

void FileHandler::stop() {
  inotify_rm_watch(fd, wd);
  close(fd);
}

void FileHandler::poll() {
  i = 0;
  length = read(fd, buffer, BUF_LEN);

  if(length < 0) {
    perror("read");
  }

  while ( i < length ) {
    struct inotify_event *event = ( struct inotify_event * ) &buffer[ i ];
    if ( event->len ) {

      if ( event->mask & IN_MODIFY) {
	if (event->mask & IN_ISDIR) {
	  string temp = "Directory was modified: ";
	  temp += event->name; 
	  temp += "\n";
	  logger.logVerbose(temp);
	}
	else {
	  string temp = "File ";
	  temp += event->name;
	  temp += " was modified with WD ";
	  temp += event->wd;
	  temp += "\n";
	  logger.logVerbose(temp);
	}
      }
 
      i += EVENT_SIZE + event->len;
    }
  }

}
