//Daniel Eisterhold
//CS4348 Project 2
//13 October 2015

#ifndef __GUEST__
#define __GUEST__

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>

class FrontDesk;
class FrontDeskEmployee;
class Bellhop;

#include "FrontDesk.h"
#include "FrontDeskEmployee.h"
#include "Bellhop.h"

class Guest {
 public:
  Guest();
  ~Guest();
  static int getNewGuestID();
  static void* start(void* guestToStart);
  void start();
  void enterHotel();
  void assignFrontDeskEmployee(FrontDeskEmployee* frontDeskEmployeeToBeAssigned);
  void assignRoom(int roomAssigned);
  bool requiresBellhop();
  void assignBellhop(Bellhop* bellhopToBeAssigned);
  void enterRoom();
  void getBags();
  void receiveBags();
  void retire();
  sem_t* bagSem();
  sem_t* roomSem();
  sem_t* deliveredSem();
  int getID();
 private:
  static int guestCount;
  int guestID;
  int bagQuantity;
  int roomNum;
  sem_t frontDeskEmployeeSem;
  FrontDeskEmployee* frontDeskEmployeeAssigned;
  sem_t bellhopReadySem;
  sem_t getBagsSem;
  sem_t inRoomSem;
  sem_t bagsDeliveredSem;
  Bellhop* bellhopAssigned;
};

#endif
