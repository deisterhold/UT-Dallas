//Daniel Eisterhold
//CS4348 Project 2
//27 October 2015

#ifndef __FRONT_DESK_EMPLOYEE__
#define __FRONT_DESK_EMPLOYEE__

#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>

class Bellhop;
class Guest;

#include "Bellhop.h"
#include "Guest.h"

class FrontDeskEmployee {
 public:
  FrontDeskEmployee();
  ~FrontDeskEmployee();
  static int getNewFrontDeskEmployeeID();
  static void* start(void* employeeToStart);
  void start();
  void assignGuest(Guest* guestToBeAssigned);
  void assignRoom();
  void assignBellhop();
  void setGuestSem(sem_t* semToSet);
  sem_t* getSem();
  void setSem(sem_t* semToSet);
  int getID();
 private:
  static int frontDeskEmployeeCount;
  int employeeID;
  Guest* currentGuest;
  sem_t* guestReady;
  sem_t* guestAssigned;
};

#endif
