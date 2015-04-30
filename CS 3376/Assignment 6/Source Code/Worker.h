//Daniel Eisterhold
//dte130030@utdallas.edu
//CS3376.502

#ifndef __WORKER__
#define __WORKER__

#include <stdio.h>
#include <stdlib.h>

#include <boost/thread.hpp>
using boost::thread;
using boost::thread_group;
using boost::mutex;
using boost::barrier;

#include <boost/interprocess/sync/interprocess_semaphore.hpp>
using boost::interprocess::interprocess_semaphore;

#include "Matrix.h"

using namespace std;

enum THREAD_STATUS {WAITING_BARRIER=0, WAITING_CONSUMER, CONSUMING, EXITED};

class Worker {
 private:
  mutex *workerMutex;
  interprocess_semaphore *workerSemaphore;
  barrier *workerBarrier;
  thread *workerThread;
  THREAD_STATUS workerStatus;
  int workerID;
  int quantityItems;
  Matrix *theMatrix;
  void updateMatrix();
 public:
  Worker(int threadID, barrier *threadBarrier, mutex *threadMutex, interprocess_semaphore *threadSem, Matrix *display);
  ~Worker();
  void init();
  void addItemsToBin(int numItems);
  void incrementSemaphore();
};

#endif
