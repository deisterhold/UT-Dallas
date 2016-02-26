//Daniel Eisterhold
//CS4348 Project 2
//13 October 2015

#include "Bellhop.h"

//Initialize bellhop counter
int Bellhop::bellhopCount = 0;

int Bellhop::getNewBellhopID() {
  return bellhopCount++;
}

Bellhop::Bellhop() {
  //Assign the bellhop a unique ID
  bellhopID = Bellhop::getNewBellhopID();

  //Initialize the current guest to none
  currentGuest = (Guest*) malloc(sizeof(*currentGuest));

  //Output that the bellhop has been created
  fprintf(stdout, "Bellhop %d created\n", getID());

  //Allocate memory for semaphores
  guestReady = (sem_t*) malloc(sizeof(*guestReady));
  guestAssigned = (sem_t*) malloc(sizeof(*guestAssigned));
}

Bellhop::~Bellhop() {
}

void* Bellhop::start(void* bellhopToStart) {
  Bellhop* bellhop = (Bellhop*) bellhopToStart;
  
  //Start the bellhop
  bellhop->start();
  
  return NULL;
}

void Bellhop::start() {
  //Get a reference to the front desk
  FrontDesk* desk = FrontDesk::get();

  //Loop forever
  while(true) {
    //If the bellhop has a guest assigned
    sem_wait(guestAssigned);
    
    //Get a guest from the queue
    Guest* temp = desk->removeGuestFromBellhopQueue();
    
    //If the queue was not empty
    if(temp != NULL) {
      //Assign the guest to bellhop
      this->assignGuest(temp);
      
      //Notify guest bellhop is getting their bags
      sem_wait(currentGuest->bagSem());

      //Get the bags from the bellhop
      this->getBags();

      //Wait for guest to be in room
      sem_wait(currentGuest->roomSem());

      //Deliver bags
      this->deliverBags();

      //Notify guest
      sem_post(currentGuest->deliveredSem());
    }
    //Otherwise
    else {
      //Exit loop
      break;
    }
  }
}

void Bellhop::assignGuest(Guest* guestToBeAssigned) {
  //Keep a reference to guest whoms bags we are carrying
  currentGuest = guestToBeAssigned;

  //Pass the guest a reference to the bellhop
  currentGuest->assignBellhop(this);
}

void Bellhop::getBags() {
  //Output that the bellhop received the bags
  fprintf(stdout, "Bellhop %d receives bags from guest %d\n", getID(), currentGuest->getID());
  fflush(stdout);
}

void Bellhop::deliverBags() {
  //Output that the bellhop delivered the bags
  fprintf(stdout, "Bellhop %d delivers bags to guest %d\n", getID(), currentGuest->getID());
  fflush(stdout);
}

void Bellhop::setGuestSem(sem_t* semToSet) {
  //Keep a reference to the semaphore
  guestReady = semToSet;
}

sem_t* Bellhop::getSem() {
  return guestAssigned;
}

void Bellhop::setSem(sem_t* semToSet) {
  guestAssigned = semToSet;
}

int Bellhop::getID() {
  //Return the ID of the bellhop
  return bellhopID;
}
