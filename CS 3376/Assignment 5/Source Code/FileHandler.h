//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#ifndef __FILEHANDLER__
#define __FILEHANDLER__

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/inotify.h>
#include <string>
#include <vector>
#include "Logger.h"

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUF_LEN (1024*(EVENT_SIZE + 16))

using namespace std;

class FileHandler {
 private:
  int length;
  int i;
  int fd;
  int wd;
  char buffer[BUF_LEN];

  string directory;
  bool encryptBackup;
  string backupPassword;
  int numBackups;
  string logFile;
  Logger logger;
  bool loggerInitialized;
  vector<string> getNamesOfBackups(string relativePath);
  string makeFilename(string fileName);
  void deleteFile(const string relativePath);
  void moveFile(const string fromLocation, const string toLocation);
  void copyFile(const string fromLocation, const string toLocation);
  void encryptFile(const string fileName, const string password);
  void decryptFile(const string fileName, const string password);
  bool fileExists(const string fileLocation);
  void makeBackup(const string fileName);
  void makeDirectory(const string folderName);
 public:
  FileHandler();
  FileHandler(const string watchDirectory, const string password);
  FileHandler(const string watchDirectory);
  ~FileHandler();
  void setNumBackups(int num);
  int getNumBackups();
  void setLogFile(const string fileName);
  string getLogFile();
  void enableVerbose();
  void disableVerbose();
  void start();
  void poll();
  void stop();
};

#endif
