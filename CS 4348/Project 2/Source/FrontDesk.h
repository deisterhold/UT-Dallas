//Daniel Eisterhold
//CS4348 Project 2
//29 October 2015

#ifndef __FRONT_DESK__
#define __FRONT_DESK__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <string>
#include <vector>

using std::vector;

class FrontDeskEmployee;
class Bellhop;
class Guest;

#include "FrontDeskEmployee.h"
#include "Bellhop.h"
#include "Guest.h"

#define NUM_FRONTDESKEMPLOYEES 1
#define NUM_BELLHOPS 1

class FrontDesk {
 public:
  FrontDesk();
  ~FrontDesk();
  static FrontDesk* get();
  static void* start(void* emptyVar);
  void start();
  void guestEnteredHotel(Guest* guestThatEntered);
  sem_t* getSem();
  sem_t* getFrontDeskEmployeeSem();
  sem_t* getBellhopSem();
  int getAvailableRoom();
  void addGuestToFrontDeskEmployeeQueue(Guest* guestToBeAdded);
  Guest* removeGuestFromFrontDeskEmployeeQueue();
  void addGuestToBellhopQueue(Guest* guestToBeAdded);
  Guest* removeGuestFromBellhopQueue();
  void quit();
 private:
  sem_t frontDeskQueueBeingAccessed;
  vector<Guest*> guestsWaitingOnFrontDeskEmployee;

  sem_t bellhopQueueBeingAccessed;
  vector<Guest*> guestsWaitingOnBellhop;

  vector<FrontDeskEmployee*> frontDeskEmployees;
  pthread_t frontDeskEmployeeThreads[NUM_FRONTDESKEMPLOYEES];

  vector<Bellhop*> bellhops;
  pthread_t bellhopThreads[NUM_BELLHOPS];

  sem_t roomAvailableSem;
  int nextRoomAvailable;

  sem_t* frontDeskEmployeeNeededSem;
  sem_t* bellhopNeededSem;

  sem_t runFrontDesk;
  bool exitFlag;

  static FrontDesk* frontDeskSingleton;
};

#endif
