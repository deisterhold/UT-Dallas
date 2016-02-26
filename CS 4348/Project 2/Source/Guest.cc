//Daniel Eisterhold
//CS4348 Project 2
//13 October 2015

#include "Guest.h"

//Initialize guest counter
int Guest::guestCount = 0;

int Guest::getNewGuestID() {
  return guestCount++;
}

Guest::Guest() {
  //Set the guest id
  guestID = Guest::getNewGuestID();

  //Assign the guest a random number of bags
  bagQuantity = rand() % 6;

  //Output that the guest was created
  fprintf(stdout, "Guest %d created\n", guestID);
  
  //Set the pointers to null
  frontDeskEmployeeAssigned = (FrontDeskEmployee*) malloc(sizeof(*frontDeskEmployeeAssigned));
  bellhopAssigned = (Bellhop*) malloc(sizeof(*bellhopAssigned));

  //Initialize semaphore so that the guest will wait
  if(sem_init(&frontDeskEmployeeSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize semaphore so that the bellhop will wait
  if(sem_init(&bellhopReadySem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize semaphore so that the guest will wait                                                
  if(sem_init(&getBagsSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize semaphore so that the guest will wait
  if(sem_init(&inRoomSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize semaphore so that the guest will wait
  if(sem_init(&bagsDeliveredSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }
}

Guest::~Guest() {
}

void* Guest::start(void* guestToStart) {
  //Cast void pointer to guest pointer
  Guest* guest = (Guest*) guestToStart;

  //Start the guest
  guest->start();

  return NULL;
}

void Guest::start() {
  //Have the guest enter the hotel
  this->enterHotel();

  //Wait to be serviced by front desk employee
  sem_wait(&frontDeskEmployeeSem);
  
  //Wait to be serviced by front desk employee
  sem_wait(&frontDeskEmployeeSem);

  //If require a bellhop
  if(this->requiresBellhop()) {
    //Wait to be assigned a bellhop
    sem_wait(&bellhopReadySem);
    
    //Request a bellhop to get bags
    this->getBags();

    //Notify the bellhop the guest is ready
    sem_post(&getBagsSem);
  }

  //Enter the room
  this->enterRoom();

  if(this->requiresBellhop()) {
    //Tell bellhop guest is in room
    sem_post(&inRoomSem);
 
    //Wait for bellhop to deliver bags
    sem_wait(&bagsDeliveredSem);

    //Receive bags from bellhop
    this->receiveBags();
  }

  //Retire for the evening
  this->retire();

  //Output that the thread is going to exit
  fprintf(stdout, "Guest %d joined\n", getID());
}

void Guest::enterHotel() {
  //Output that the guest entered the hotel and number of bags
  if(bagQuantity == 1) {
    fprintf(stdout, "Guest %d enters hotel with %d bag\n", getID(), bagQuantity);
  }
  else {
    fprintf(stdout, "Guest %d enters hotel with %d bags\n", getID(), bagQuantity);
  }

  //Get a reference to the front desk
  FrontDesk* desk = FrontDesk::get();

  //Add self to the front desk queue
  desk->guestEnteredHotel(this);
}

void Guest::assignFrontDeskEmployee(FrontDeskEmployee* frontDeskEmployeeToBeAssigned) {
  //Set the variable so we have a refernce to the front desk employee
  frontDeskEmployeeAssigned = frontDeskEmployeeAssigned;

  //Pass a reference to the front desk employee semaphore to the front desk employee
  frontDeskEmployeeAssigned->setGuestSem(&frontDeskEmployeeSem);

  //Increment semaphore
  sem_post(&frontDeskEmployeeSem);
}

void Guest::assignRoom(int roomAssigned) {
  //Set the guests room number
  roomNum = roomAssigned;
  
  //Output that guest got their room key
  fprintf(stdout, "Guest %d receives room key for room %d from front desk employee %d\n", getID(), roomNum, frontDeskEmployeeAssigned->getID());

  //Increment semaphore
  sem_post(&frontDeskEmployeeSem);
}

void Guest::assignBellhop(Bellhop* bellhopToBeAssigned) {
  //Set the bellhop assigned to the guest
  bellhopAssigned = bellhopToBeAssigned;
  
  //Pass a reference to the bellhop that lets the bellhop know the guest is in their room
  bellhopAssigned->setGuestSem(&inRoomSem);

  //Let the guest know he was assigned a bellhop
  sem_post(&bellhopReadySem);
}

void Guest::enterRoom() {
  //Output that guest entered room 
  fprintf(stdout, "Guest %d enters room %d\n", getID(), roomNum);
}

void Guest::getBags() {
  fprintf(stderr, "Guest %d requests help with bags\n", getID());
}

void Guest::receiveBags() {
  //Output that the guest received their bags from the bellhop
  fprintf(stdout, "Guest %d receives bags from bellhop %d and gives tip\n", getID(), bellhopAssigned->getID());
}

void Guest::retire() {
  //Output that the guest is retiring for the evening
  fprintf(stdout, "Guest %d retires for the evening\n", getID());
}

bool Guest::requiresBellhop() {
  //If more than 2 bags return true
  if(bagQuantity > 2) {
    return true;
  }

  //Otherwise return false
  return false;
}

int Guest::getID() {
  //Return the number of the guest
  return guestID;
}

sem_t* Guest::bagSem() {
  return &getBagsSem;
}

sem_t* Guest::roomSem() {
  return &inRoomSem;
}

sem_t* Guest::deliveredSem() {
  return &bagsDeliveredSem;
}
