//Daniel Eisterhold
//CS4348 Project 2
//27 October 2015

#include "FrontDeskEmployee.h"

int FrontDeskEmployee::frontDeskEmployeeCount = 0;

FrontDeskEmployee::FrontDeskEmployee() {
  //Set employee id
  employeeID = getNewFrontDeskEmployeeID();

  //Reserve memory for the semaphore
  guestReady = (sem_t*) malloc(sizeof(*guestReady));
  guestAssigned = (sem_t*) malloc(sizeof(*guestAssigned));
  
  //Variable to hold the current guest the employee is checking in
  currentGuest = NULL;

  //Print status
  fprintf(stdout, "Front desk employee %d created\n", getID());

  //Initialize semaphore so that we will wait until a guest has been assigned
  sem_init(guestAssigned, 0, 0);
}

FrontDeskEmployee::~FrontDeskEmployee() {
}

void* FrontDeskEmployee::start(void* employeeToStart) {
  //Cast the void pointer to a front desk employee pointer
  FrontDeskEmployee* employee = (FrontDeskEmployee*) employeeToStart;

  //Start the front desk employee
  employee->start();

  return NULL;
}

void FrontDeskEmployee::start() {
  //Get a reference to the front desk
  FrontDesk* desk = FrontDesk::get();

  //Loop forever
  while(true) {
    //If the front desk employee has a guest assigned
    sem_wait(guestAssigned);
    
    //Get a guest from the queue
    Guest* temp = desk->removeGuestFromFrontDeskEmployeeQueue();
    
    if(temp != NULL) {
      //Assign the guest
      this->assignGuest(temp);
      
      sem_post(guestReady);

      //Assign the current guest a room
      this->assignRoom();

      //Wait for guest to acknowledge they received a room
      sem_wait(guestReady);

      //If the guest requires a bellhop
      if(currentGuest->requiresBellhop()) {
	//Assign guest a bellhop
	this->assignBellhop();
      }
    }
    //Exit loop
    else {
      break;
    }
  }
}

void FrontDeskEmployee::assignGuest(Guest* guestToBeAssigned) {
  //Set the current guest to the passed value
  currentGuest = guestToBeAssigned;

  //Pass a reference of the front desk employee serving the guest
  currentGuest->assignFrontDeskEmployee(this);
}

void FrontDeskEmployee::assignRoom() {
  //Get a reference to the front desk
  FrontDesk* desk = FrontDesk::get();

  int room = desk->getAvailableRoom();

  //Output that the employee assigned a guest their room
  fprintf(stdout, "Front desk employee %d registers guest %d and assigns room %d\n", getID(), currentGuest->getID(), room);
  
  //Pass the room number to the gueset
  currentGuest->assignRoom(room);
}

void FrontDeskEmployee::assignBellhop() {
  //Get a reference to the front desk
  FrontDesk* desk = FrontDesk::get();
  
  //Add the guest to the bellhop queue
  desk->addGuestToBellhopQueue(currentGuest);

  //Notify the bellhops there is a guest to be serviced
  sem_post(desk->getBellhopSem());
}

void FrontDeskEmployee::setGuestSem(sem_t* semToSet) {
  //Set the variable
  guestReady = semToSet;
}

sem_t* FrontDeskEmployee::getSem() {
  return guestAssigned;
}

void FrontDeskEmployee::setSem(sem_t* semToSet) {
  guestAssigned = semToSet;
}

int FrontDeskEmployee::getID() {
  return employeeID;
}

int FrontDeskEmployee::getNewFrontDeskEmployeeID() {
  //Increment front desk employee ID counter and return its value
  return frontDeskEmployeeCount++;
}
