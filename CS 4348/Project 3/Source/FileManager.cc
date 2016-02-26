//Daniel Eisterhold
//CS4348 Project 3
//10 November 2015

#include "FileManager.h"

// MARK: File Manager Static Methods and Properties
FileManager* FileManager::instance = NULL;

FileManager* FileManager::get() {
  // If the file manager has not been created
  if(instance == NULL) {
    // Create a file manager instance
    instance = new FileManager();
  }
  // Return the file manager instance
  return instance;
}

// MARK: Constructor and Destructor
FileManager::FileManager() {
  // Create the semaphore
  sem_init(&vectorProtector, 0, 1);
}

FileManager::~FileManager() {
  // Destroy the semaphore
  sem_destroy(&vectorProtector);
}

// MARK: Public Methods

int FileManager::create(string nameOfFile) {
  // Check to see if file exists
  if(exists(nameOfFile)) {
    // Return negative one
    return -1;
  }
  else {
    // Obtain lock on dictionary
    sem_wait(&vectorProtector);

    cerr<<"Creating file: "<<nameOfFile<<endl;
    // Initialize file, filename, and file semaphore
    fileVector.push_back(vector<uint8_t>());
    fileNameVector.push_back(nameOfFile);
    semVector.push_back(sem_t());

    // Initialize semaphore
    sem_init(&semVector.back(), 0, 1);

    // Release lock on dictionary
    sem_post(&vectorProtector);

    // Return index of filecreated
    return fileNameVector.size()-1;
  }
}

void FileManager::destroy(string nameOfFile) {
  // Check to see if file exists
  if(exists(nameOfFile)) {
    int index = indexOf(nameOfFile);

    // Obtain lock
    sem_wait(&vectorProtector);

    fileVector.erase(fileVector.begin() + index);
    fileNameVector.erase(fileNameVector.begin() + index);
    semVector.erase(semVector.begin() + index);

    // Release lock on dictionary
    sem_post(&vectorProtector);
  }
}

bool FileManager::exists(string nameOfFile) {
  // If the index is negative
  if(indexOf(nameOfFile) < 0) {
    // Return false
    return false;
  }
  else {
    // Return true
    return true;
  }
}

int FileManager::indexOf(string nameOfFile) {
  // Variable to hold index of file
  int fileIndex = -1;

  // Obtain lock on vector
  sem_wait(&vectorProtector);

  // Iterate through the vector
  for(uint index = 0; index < fileNameVector.size(); index++) {
    // If the file name is in the vector
    if(nameOfFile.compare(fileNameVector[index]) == 0) {
      // Return the index of the file name
      fileIndex = index;
      // Break out of the loop
      break;
    }
  }

  // Release lock on vector
  sem_post(&vectorProtector);

  // Return index of the file
  return fileIndex;
}

vector<string> FileManager::listOfFiles() {
  return fileNameVector;
}

vector<uint8_t>* FileManager::startEditing(string nameOfFile) {
  if(exists(nameOfFile)) {
    // Variable to hold index of file
    int index = indexOf(nameOfFile);

    // Obtain lock on file
    sem_wait(&semVector[index]);

    // Obtain lock on vector
    sem_wait(&vectorProtector);

    // Get pointer to byte vector
    vector<uint8_t>* file = &fileVector[index];

    // Release lock on vector
    sem_post(&vectorProtector);

    cerr<<"Started editing: "<<nameOfFile<<endl;

    //Return vector corresponding to file name
    return file;
  }
  else {
    cerr<<"Unable to start editing, file not found"<<endl;
    return NULL;
  }
}

void FileManager::stopEditing(string nameOfFile) {
  if(exists(nameOfFile)) {
    // Variable to hold index of file
    int index = indexOf(nameOfFile);

    // Release lock on file
    sem_post(&semVector[index]);
    cerr<<"Stopped editing: "<<nameOfFile<<endl;
  }
  else {
    cerr<<"Unable to stop editing, file not found"<<endl;
  }
}
