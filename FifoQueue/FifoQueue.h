/**
 * @file FifoQueue.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief FifoQueue header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _FIFO_QUEUE_H_
#define _FIFO_QUEUE_H_

#include <queue>
#include <mutex>
#include <condition_variable>
#include "../Truck/Truck.h"

namespace FifoQueue
{

  /**
   * @brief Blocking FIFO Queue
  */
  class FifoQueue
  {
    public:

    /**
     * @brief Constructor
    */
    FifoQueue();

    /**
     * @brief Destructor
    */
    ~FifoQueue();

    /**
     * @brief Remove truck pointer from front of queue and return
     * 
     * @return Pointer to truck that was removed
    */
    Truck::Truck* pop();

    /**
     * @brief Return Truck pointer from front (but don't remove from queue)
     * 
     * @return Pointer to truck at front of the queue
    */
    Truck::Truck* front();

    /**
     * @brief Entere truck pointer into end of the queue
     * 
     * @param value Truck pointer that will be entered into the queue
    */
    void push(Truck::Truck* value);

    /**
     * @brief Return TRUE if queue is empty, else FALSE
     * @return Whether queue is empty or not
     * @retval true Queue is empty
     * @retval false Queue is not empty
    */
    bool empty();

    /**
     * @brief Block wait for done signal which is signaled when item is popped off the queue
    */
    void waitForSignalDone();

    private:

    std::queue<Truck::Truck*> q; //!< Queue to hold trucks in line
    std::mutex mtx; //!< Mutex to protect the queue 
    std::condition_variable cv; //!< Used to signal 
    bool done; //!< True if item popped of queue, else False

  };

}

#endif