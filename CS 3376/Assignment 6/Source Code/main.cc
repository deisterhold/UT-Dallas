//Daniel Eisterhold
//dte130030@utdallas.edu
//CS 3376.502

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

#include <boost/thread.hpp>
using boost::thread;
using boost::thread_group;
using boost::mutex;
using boost::barrier;

#include "Worker.h"

#define NUM_THREADS 25

using namespace std;

//Flag to know when to exit
bool startShutdown = false;

void signalHandler(int sigNum) {
  switch(sigNum) {
    case SIGTERM:
    case SIGINT:
      //printf("\nInterrupt Signal\n");
      startShutdown = true;
      break;
    default:
      break;
  }
}

int main(int argc, char* argv[]) {
  //Tell system what signals to listen to
  signal(SIGINT, signalHandler);
  signal(SIGTERM, signalHandler);

  //Barrier to make sure all threads are created before running
  barrier theBarrier(NUM_THREADS+1);

  //Array of sempaphores to synchonize between the producer and workers
  interprocess_semaphore *workerSemaphores[NUM_THREADS];

  //Lock to prevent screen from been updated simultaneously
  mutex matrixLock;
  
  //Array to hold all the workers
  Worker *workers[NUM_THREADS];

  //Matrix for displaying output to screen
  Matrix screen = Matrix();

  thread_group threadGroup;
  thread *consumerThread;
  
  for(int counter = 0; counter < NUM_THREADS; counter++) {
    workerSemaphores[counter] = new interprocess_semaphore(0);
    workers[counter] = new Worker(counter, &theBarrier,&matrixLock,workerSemaphores[counter],&screen);
    consumerThread = new boost::thread(&Worker::init,workers[counter]);
    threadGroup.add_thread(consumerThread);
  }
  
  //Make producer wait 5 seconds
  //To allow other threads to be created
  sleep(5);

  //Wait for all the threads to be ready
  theBarrier.wait();

  //Sleep again to show that all bins are empty
  sleep(5);

  //Main Program Here
  while(!startShutdown) {
    int threadNum = rand() % NUM_THREADS;
    int num = rand() % ((20-10)+1)+10;
    workers[threadNum]->addItemsToBin(num);
    sleep(1);
  }

  //Tell all the works to exit when all their bins are empty
  for(int counter = 0; counter < NUM_THREADS; counter++) {
    workers[counter]->incrementSemaphore();
  }

  //Wait for all threads to return
  threadGroup.join_all();

  return 0;
}
