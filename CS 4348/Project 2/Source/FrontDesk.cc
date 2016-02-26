//Daniel Eisterhold
//CS4348 Project 2
//4 November 2015

#include "FrontDesk.h"

//Initialize the singleton
FrontDesk* FrontDesk::frontDeskSingleton = NULL;

FrontDesk::FrontDesk() {
  //Initialize the current room number
  nextRoomAvailable = 0;

  //Initialize the semaphore that protects the room available counter
  if(sem_init(&roomAvailableSem, 0, 1)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize the semaphore that protects the guests waiting to be serviced by a front desk employee
  if(sem_init(&frontDeskQueueBeingAccessed, 0, 1)) {
    fprintf(stderr,"Error initializing semaphore\n");
    exit(1);
  }

  //Initialize the vector that holds the guests waiting to be serviced by the front desk employees
  guestsWaitingOnFrontDeskEmployee = vector<Guest*>();

  //Initialize the semaphore that protects the guests waiting to be serviced by a bellhop
  if(sem_init(&bellhopQueueBeingAccessed, 0, 1)) {
    fprintf(stderr,"Error initializing semaphore\n");
    exit(1);
  }

  //Initialize the vector that holds the guests waiting to be serviced by the bellhops
  guestsWaitingOnBellhop = vector<Guest*>();

  //Initialize the vector containing the Front Desk Employees
  frontDeskEmployees = vector<FrontDeskEmployee*>();

  //Initialize the vector containing the Bellhops
  bellhops = vector<Bellhop*>();
  
  //Initialize semaphore for knowing when to exit
  if(sem_init(&runFrontDesk, 0, 1)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Allocate memory for semaphores
  frontDeskEmployeeNeededSem = (sem_t*) malloc(sizeof(*frontDeskEmployeeNeededSem));
  bellhopNeededSem = (sem_t*) malloc(sizeof(*bellhopNeededSem));

  //Initialize semaphore for knowing when a front desk employee is needed
  if(sem_init(frontDeskEmployeeNeededSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  //Initialize semaphore for knowing when a bellhop is needed
  if(sem_init(bellhopNeededSem, 0, 0)) {
    fprintf(stderr, "Error initializing semaphore\n");
    exit(1);
  }

  exitFlag = false;
}

FrontDesk::~FrontDesk() {
}

void* FrontDesk::start(void* emptyVar) {
  //Get the front desk
  FrontDesk* desk = FrontDesk::get();
  
  //Call the start method and pass it the semaphore
  desk->start();

  return NULL;
}

void FrontDesk::start() {
  //Loop forever
  while(true) {
    //Wait until a guest arrives
    sem_wait(&runFrontDesk);

    //If the flag has not been flipped create the threads
    if(!exitFlag) {
      //Flip flag so that it only runs once
      exitFlag = true;

      //Initialize front desk employee threads
      for(int index = 0; index < NUM_FRONTDESKEMPLOYEES; index++) {
	//Create new employee
	FrontDeskEmployee* employee = new FrontDeskEmployee();

	//Set the shared semaphore
	employee->setSem(frontDeskEmployeeNeededSem);

	//Add employee to vector
	frontDeskEmployees.push_back(employee);
	
	//Create and run the thread
	pthread_create(&frontDeskEmployeeThreads[index], NULL, FrontDeskEmployee::start, (void*) employee);
	//Tell employee to start serving guests
	sem_post(employee->getSem());
      }
      
      //Initialize bellhop threads
      for(int index = 0; index < NUM_BELLHOPS; index++) {
	//Create new bellhop
	Bellhop* bellhop = new Bellhop();
	
	//Set the shared semaphore
	bellhop->setSem(bellhopNeededSem);
	
	//Add bellhop to vector
	bellhops.push_back(bellhop);

	//Create and run the thread
	pthread_create(&bellhopThreads[index], NULL, Bellhop::start, (void*) bellhop);
      }
    }
    //Break out of loop
    else {
      //For all the front desk employees
      for(uint index = 0; index < frontDeskEmployees.size();index++) {
	//Increment semaphore so bellhops exit
	sem_post(frontDeskEmployees[index]->getSem());
	
	//Wait for the front desk employee thread to join
	pthread_join(frontDeskEmployeeThreads[index], NULL);
      }
      
      //For all the bellhops
      for(uint index = 0; index < bellhops.size(); index++) {
	//Increment semaphore so bellhops exit
	sem_post(bellhops[index]->getSem());
	
	//Wait for the bellhop thread to join
	pthread_join(bellhopThreads[index], NULL);
      }

      //Break from loop
      break;
    }
  }
}

sem_t* FrontDesk::getSem() {
  //Return the semaphore
  return &runFrontDesk;
}

sem_t* FrontDesk::getFrontDeskEmployeeSem() {
  return frontDeskEmployeeNeededSem;
}

sem_t* FrontDesk::getBellhopSem() {
  return bellhopNeededSem;
}

void FrontDesk::guestEnteredHotel(Guest* guestThatEntered) {
  //Add the guest to the queue
  addGuestToFrontDeskEmployeeQueue(guestThatEntered);
}

void FrontDesk::addGuestToFrontDeskEmployeeQueue(Guest* guestToBeAdded) {
  //Wait for whoever is currently accessing the queue to finish
  sem_wait(&frontDeskQueueBeingAccessed);

  //Add the guest to the end of the queue
  guestsWaitingOnFrontDeskEmployee.push_back(guestToBeAdded);

  //Increment the semaphore so someone else can access the queue
  sem_post(&frontDeskQueueBeingAccessed);
}

void FrontDesk::addGuestToBellhopQueue(Guest* guestToBeAdded) {
  //Wait for whoever is currently accessing the queue to finish
  sem_wait(&bellhopQueueBeingAccessed);

  //Add the guest to the end of the queue
  guestsWaitingOnBellhop.push_back(guestToBeAdded);

  //Increment the semaphore so someone else can access the queue
  sem_post(&bellhopQueueBeingAccessed);
}

Guest* FrontDesk::removeGuestFromFrontDeskEmployeeQueue() {
  //Wait for whoever is currently accessing the queue to finish
  sem_wait(&frontDeskQueueBeingAccessed);

  //Temp variable for holding guest
  Guest* temp;
  
  //If there are guests in the queue
  if(guestsWaitingOnFrontDeskEmployee.size() > 0) {
    //Get a reference to the first quest in the queue
    temp = guestsWaitingOnFrontDeskEmployee.front();

    //Delete the first quest in the queue
    guestsWaitingOnFrontDeskEmployee.erase(guestsWaitingOnFrontDeskEmployee.begin());
  }
  //Otherwise return nothing
  else {
    //Set temp to none
    temp = NULL;
  }

  //Increment the semaphore so someone else can access the queue
  sem_post(&frontDeskQueueBeingAccessed);
  
  return temp;
}

Guest* FrontDesk::removeGuestFromBellhopQueue() {
  //Wait for whoever is currently accessing the queue to finish
  sem_wait(&bellhopQueueBeingAccessed);
  
  //Temp variable for holding guest
  Guest* temp;

  //If there are guests in the queue
  if(guestsWaitingOnBellhop.size() > 0) {
    //Get a reference to the first quest in the queue
    temp = guestsWaitingOnBellhop.front();

    //Delete the first quest in the queue
    guestsWaitingOnBellhop.erase(guestsWaitingOnBellhop.begin());
  }
  //Otherwise return nothing
  else {
    //Set temp to none
    temp = NULL;
  }

  //Increment the semaphore so someone else can access the queue
  sem_post(&bellhopQueueBeingAccessed);

  return temp;
}

int FrontDesk::getAvailableRoom() {
  //Wait if someone else is accessing
  sem_wait(&roomAvailableSem);
  
  //Increment room number and store in a temp variable
  int temp = ++nextRoomAvailable;
  
  //Increment so someone else can access it
  sem_post(&roomAvailableSem);
  
  //Return the temp variable
  return temp;
}

FrontDesk* FrontDesk::get() {
  //If the singleton is not initialized
  if(frontDeskSingleton == NULL) {
    //Initialize it
    frontDeskSingleton = new FrontDesk();
  }

  //Return the singleton
  return frontDeskSingleton;
}

void FrontDesk::quit() {
  //Increment semaphore
  sem_post(&runFrontDesk);
}
