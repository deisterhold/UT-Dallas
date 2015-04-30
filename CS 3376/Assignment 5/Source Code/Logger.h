//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#ifndef __LOGGER__
#define __LOGGER__

#include <stdio.h>
#include <stdlib.h>
#include <string>

using namespace std;

class Logger {
 private:
  int stdoutfd;
  int stderrfd;
  fpos_t stdoutpos;
  fpos_t stderrpos;
  string fileName;
  bool verbose;
  string getDate();

  public:
  Logger();
  Logger(const string fileLocation);
  ~Logger();

  void setLogFile(const string fileLocation);
  string getLogFile();

  void log(const string message);
  void logVerbose(const string message);
  void logError(const string message);
  void logErrorVerbose(const string message);

  void enableVerbose();
  void disableVerbose();

  void start();
  void stop();
};

#endif
