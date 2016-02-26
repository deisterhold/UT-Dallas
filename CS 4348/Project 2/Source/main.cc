//Daniel Eisterhold
//CS4348 Project 2
//13 October 2015

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#include "FrontDesk.h"

static const uint NUM_GUESTS = 25;

int main(int argc, char *argv[]) {
  //Thread for the front desk
  pthread_t frontDeskThread;

  //Thread for each of the guests
  pthread_t guestThreads[NUM_GUESTS];

  //Pointer for front desk
  FrontDesk* frontDesk;

  //Set the seed of the random number generator to the current time
  srand(time(NULL));

  //Print that the simulation is starting
  fprintf(stdout, "Simulation starts\n");

  //Initialize front desk
  frontDesk = FrontDesk::get();

  //Create the thread and start the front desk
  pthread_create(&frontDeskThread, NULL, FrontDesk::start, NULL);

  //Create the number of guests that we want
  for(uint guestNum = 0; guestNum < NUM_GUESTS; guestNum++) {
    //Create the guest
    Guest* tempGuest = new Guest();

    //Create the thread and start the guest
    pthread_create(&guestThreads[guestNum], NULL, Guest::start, (void*)tempGuest);
  }

  //Wait for all the guest threads to exit
  for(uint index = 0; index < NUM_GUESTS; index++) {
    pthread_join(guestThreads[index], NULL);
  }

  //Tell the front desk thread to stop executing
  frontDesk->quit();

  //Wait for the front desk thread to exit
  pthread_join(frontDeskThread, NULL);

  //Print that the simulation is ending
  fprintf(stdout, "Simulation ends\n");

  return 0;
}
