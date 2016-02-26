//Daniel Eisterhold
//CS4348 Project 2
//13 October 2015

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

#include "Guest.h"

#ifndef __BELLHOP__
#define __BELLHOP__

class Bellhop {
 public:
  Bellhop();
  ~Bellhop();
  static int getNewBellhopID();
  static void* start(void* bellhopToStart);
  void start();
  void assignGuest(Guest* guestToBeAssigned);
  void getBags();
  void deliverBags();
  void setGuestSem(sem_t* semToSet);
  sem_t* getSem();
  void setSem(sem_t* semToSet);
  int getID();
 private:
  static int bellhopCount;
  int bellhopID;
  int _bagQuantity;
  double totalTips;
  Guest* currentGuest;
  sem_t* guestReady;
  sem_t* guestAssigned;
};

#endif
