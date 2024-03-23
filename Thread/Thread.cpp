#include "Thread.h"

namespace Thread
{
  Thread::Thread()
  {}

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

}