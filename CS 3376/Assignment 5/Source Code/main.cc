//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string>
#include <fstream>
#include <map>

#include "FileHandler.h"

using namespace std;

bool reReadConfigFile = false;

//Functions defined in other source files
extern map<string,string> parseCommandLine(int argc, char *argv[]);
extern map<string,string> parseConfigFile(string fileLocation);

bool checkFileExists(string fileLocation) {
  ifstream inputFile;
  inputFile.open(fileLocation.c_str());
  if(inputFile) {
    inputFile.close();
    return true;
  }
  else {
    inputFile.close();
    return false;
  }
}

void killCHILD() {
  //Exit if PID file doesn't exists                                                     
  if(!checkFileExists("cs3376dirmond.pid")) return;
  pid_t childPID;
  ifstream inputFile;
  inputFile.open("cs3376dirmond.pid");
  if(inputFile) {
    inputFile>>childPID;
  }
  else fprintf(stderr,"Error reading PID file.\n");
  string fullCommand = "kill -9 ";
  fullCommand += childPID;
  fprintf(stdout,"Calling \"%s\"\n",fullCommand.c_str());
  system(fullCommand.c_str());
}

void signalHandler(int sigNum) {
  switch(sigNum) {
  case SIGINT:
    killCHILD();
    system("rm -f cs3376dirmond.pid");
    printf("Removing PID file.\n");
    break;
  case SIGTERM:
    killCHILD();
    system("rm -f cs3376dirmond.pid");
    printf("Removing PID file.\n");
    break;
  case SIGHUP:
    fprintf(stdout,"Received SIGHUP signal, reading config file again.\n");
    reReadConfigFile = true;
    break;
  default:
    break;
  }
}

int main(int argc, char *argv[]) {
  map<string,string> arguments = parseCommandLine(argc, argv);
  map<string,string> settings = parseConfigFile(arguments["configFile"]);
  FileHandler handler;
  pid_t childPID;

  if(arguments["daemonMode"] == "true") {
    if(checkFileExists("cs3376dirmond.pid")) {
      //Exit with error because daemon is already running
      fprintf(stderr, "Daemon is already running.\n");
      exit(1);
    }
    else {
      childPID = fork();
      if(childPID < 0) {
	fprintf(stderr, "Error creating child process");
	exit(1);
      }
      else if(childPID == 0) {
	//printf("Inside child process\n");
      }
      else {
	//printf("Inside parent process\n");
	ofstream processFile;
	processFile.open("cs3376dirmond.pid");
	if(processFile) {
	  processFile<<childPID<<endl;
	}
	else {
	  fprintf(stderr,"Error opening PID file.\n");
	}
	processFile.close();
	exit(0);
      }
    }
  }

  //Register signal handlers
  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);
  signal(SIGHUP, signalHandler);

  //If there was a password in the config file
  //Start the FileHandler in encrypted mode
  if(settings["password"].length() > 0) {
    handler = FileHandler(settings["watchDirectory"], settings["password"]);
  }
  else {
    handler = FileHandler(settings["watchDirectory"]);
  }
  
  //Set the number of versions too keep and log file
  handler.setNumBackups(atoi(settings["numVersions"].c_str()));
  handler.setLogFile(settings["logFile"]);
  if(settings["verbose"] == "true") handler.enableVerbose();
  else handler.disableVerbose();

  //Start running inotify
  handler.start();
  while(1);

  return 0;

  while(1) {
    fprintf(stderr,"Looping.\n");
    handler.poll();
    if(reReadConfigFile) {
      settings = parseConfigFile(arguments["configFile"]);
      handler.setNumBackups(atoi(settings["numVersions"].c_str()));
      handler.setLogFile(settings["logFile"]);
      if(settings["verbose"] == "true") handler.enableVerbose();
      else handler.disableVerbose();
    }
    sleep(1);
  }

  //Program should never reach here
  handler.stop();
  return 0;
}
