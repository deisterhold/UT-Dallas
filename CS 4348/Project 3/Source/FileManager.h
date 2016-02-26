//Daniel Eisterhold
//CS4348 Project 3
//10 November 2015

#ifndef __FILE_MANAGER_H__
#define __FILE_MANAGER_H__

#include <string>
#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <stdlib.h>
#include <inttypes.h>
#include <semaphore.h>

using namespace std;

class FileManager {
 public:
  FileManager();
  ~FileManager();
  static FileManager* get();
  int create(string);
  void destroy(string);
  int indexOf(string);
  bool exists(string);
  vector<string> listOfFiles();
  vector<uint8_t>* startEditing(string);
  void stopEditing(string);
 private:
  static FileManager* instance;
  vector< vector<uint8_t> > fileVector;
  vector<string> fileNameVector;
  vector<sem_t> semVector;
  sem_t vectorProtector;
};

#endif
