//Daniel Eisterhold
//CS4348 Project 3
//15 November 2015

#ifndef __SERVER_H__
#define __SERVER_H__

#include <iostream>
#include <vector>
#include <stdlib.h>
#include <unistd.h>
#include <inttypes.h>
#include <string.h>

#include <pthread.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>

#include "FileManager.h"
#include "Commands.h"

using namespace std;

#define MAX_NUMCLIENTS 5

class Server {
 public:
  Server();
  ~Server();
  void start(uint16_t);
  static void* handleClient(void*);
 private:
  static vector<pthread_t> serverThreads;
  pthread_attr_t threadAttributes;
  int socketFD;
  struct sockaddr_in serverInfo;
  struct hostent* hostInfo;
};

#endif
