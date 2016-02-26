//Daniel Eisterhold
//CS4348 Project 3
//15 November 2015

#ifndef __CLIENT_H__
#define __CLIENT_H__

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#include <sys/stat.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "Commands.h"

using namespace std;

class Client {
 public:
  Client();
  ~Client();
  void start(string, uint16_t);
 private:
  void processMenuChoice(int);
  int presentMenuToUser();
  string getFilename(bool localFile = false);
  void listFiles();
  void uploadFile();
  void downloadFile();
  void deleteFile();
  int socketFD;
  struct sockaddr_in clientInfo;
  struct hostent* hostInfo;
};

#endif
