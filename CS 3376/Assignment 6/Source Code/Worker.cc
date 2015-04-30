//Daniel Eisterhold
//dte130030@utdallas.edu
//CS3376.502

#include "Worker.h"
/*
mutex *workerMutex;
  barrier *workerBarrier;
  thread *workerThread;
  THREAD_STATUS workerStatus;
  int workerID;
  int quantityItems;
*/

Worker::Worker(int threadID, barrier *threadBarrier, mutex *threadMutex, interprocess_semaphore *threadSem, Matrix *display) {
  workerSemaphore = threadSem;
  workerID = threadID;
  workerBarrier = threadBarrier;
  workerMutex = threadMutex;
  theMatrix = display;
  quantityItems = 0;
  workerStatus = WAITING_BARRIER;
}

Worker::~Worker() {

}

void Worker::init() {
  //printf("Thread: %d, is waiting on barrier...\n", workerID);
  workerStatus = WAITING_BARRIER;
  updateMatrix();
  workerBarrier->wait();
  //printf("Thread: %d, is now running...\n", workerID);
  //Loop forever
  while(1) {
    //Wait until there is work to do
    workerStatus = WAITING_CONSUMER;
    updateMatrix();
    workerSemaphore->wait();
    
    //If there are no items then exit
    if(quantityItems == 0) {
      workerStatus = EXITED;
      updateMatrix();
      return;
    }
    //Otherise do work
    else {
      workerStatus = CONSUMING;
      quantityItems--;
      updateMatrix();
      sleep(1);
    }
  }
}

void Worker::updateMatrix() {
  workerMutex->lock();
  //Buffer to hold matrix text
  char buffer[16];
  
  switch(workerStatus) {
  case WAITING_BARRIER:
    sprintf(buffer,"tid:%d S:%s Q:%d",workerID,"B",quantityItems);
    break;
  case WAITING_CONSUMER:
    sprintf(buffer,"tid:%d S:%s Q:%d",workerID,"W",quantityItems);
    break;
  case CONSUMING:
    sprintf(buffer,"tid:%d S:%s Q:%d",workerID,"C",quantityItems);
    break;
  case EXITED:
    sprintf(buffer,"tid:%d S:%s Q:%d",workerID,"E",quantityItems);
    break;
  default:
    break;
  }
  int row = (workerID/5)+1;
  int column = (workerID%5)+1;

  theMatrix->setCell(row, column, buffer);
  workerMutex->unlock();
}

void Worker::addItemsToBin(int numItems) {
  workerMutex->lock();
  for(int counter = 0; counter < numItems; counter++) {
    quantityItems++;
    workerSemaphore->post();
  }
  //Do stuff in here
  workerMutex->unlock();
  updateMatrix();
}

void Worker::incrementSemaphore() {
  workerMutex->lock();
  workerSemaphore->post();
  workerMutex->unlock();
}
