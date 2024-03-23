#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace Thread {

  class Thread
  {
    public:

    Thread();

    void start();

    static void* callback(void *ctx);

    protected:

    virtual void runFunc() = 0;

    private:

    pthread_t thread;

  };

}

#endif