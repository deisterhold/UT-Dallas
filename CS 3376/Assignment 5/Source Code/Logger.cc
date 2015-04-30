//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include "Logger.h"

string Logger::getDate() {                                                                                  
  string command = "date +%Y/%m/%d_%H:%M:%S";                                                                        
  FILE *input;                                                                                                                        
  input = popen(command.c_str(), "r");                                                                                                
  if(input == NULL) {                                                                                                                 
    fprintf(stderr,"Error creating filename.\n");                                                                                           
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
    return newFilename.substr(0, newFilename.length()-1);                                                                                                               
  }                                                                                                                                   
}

Logger::Logger(){
}

Logger::Logger(const string fileLocation){
  fileName = fileLocation;
}

Logger::~Logger(){
  stop();
}

void Logger::log(const string message) {
  fprintf(stdout, "%s %s",getDate().c_str(),message.c_str());
}

void Logger::logVerbose(string message) {
  if(verbose) {
    log(message);
  }
}

void Logger::logError(string message) {
  log("Error: " + message);
}

void Logger::logErrorVerbose(string message) {
  if(verbose) {
    logError(message);
  }
}

void Logger::setLogFile(const string fileLocation) {
  fileName = fileLocation;
}

string Logger::getLogFile() {
  return fileName;
}


void Logger::enableVerbose() {
  verbose = true;
}

void Logger::disableVerbose() {
  verbose = false;
}

void Logger::start() {
  fflush(stdout);
  fgetpos(stdout, &stdoutpos);
  stdoutfd = dup(fileno(stdout));
  freopen(fileName.c_str(), "w", stdout);

  fflush(stderr);
  fgetpos(stderr, &stderrpos);
  stderrfd = dup(fileno(stderr));
  freopen(fileName.c_str(), "w", stderr);
}

void Logger::stop() {
  fflush(stdout);
  dup2(stdoutfd, fileno(stdout));
  close(stdoutfd);
  clearerr(stdout);
  fsetpos(stdout, &stdoutpos);

  fflush(stderr);
  dup2(stderrfd, fileno(stderr));
  close(stderrfd);
  clearerr(stderr);
  fsetpos(stderr, &stderrpos);
}
