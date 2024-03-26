/**
 * @file Thread.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Thread implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include "Thread.h"

namespace Thread
{
  Thread::Thread()
  {}

  Thread::~Thread()
  {
    pthread_join(this->thread, NULL);
  }

  void *Thread::callback(void *arg)
  {
    Thread *self = static_cast<Thread*>(arg);
    self->runFunc();

     return NULL;
  }

  void Thread::start()
  {
    pthread_create(&this->thread, NULL, Thread::callback, this);

  }

  void Thread::exit()
  {

  }

}