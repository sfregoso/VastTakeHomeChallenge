#ifndef _FIFO_QUEUE_H_
#define _FIFO_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include "../Truck/Truck.h"

namespace FifoQueue
{

  class FifoQueue
  {
    public:

    FifoQueue(); //!< Constructor

    ~FifoQueue(); //!< Destructor

    Truck::Truck* pop();

    void push(Truck::Truck* value);

    bool empty();

    void waitForSignalDone();

    private:

    std::queue<Truck::Truck*> q; //!< Queue to hold trucks in line
    std::mutex mtx; //!< Mutex to protect the queue 
    std::condition_variable cv; //!< Used to signal 
    bool done;

  };

}

#endif