/**
 * @file Thread.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Thread header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _THREAD_H_
#define _THREAD_H_

#include <pthread.h>

namespace Thread {

  /**
   * @brief C++ Thread class wrapper around POSIX threads
  */
  class Thread
  {
    public:

    /**
     * @brief Constructor
    */
    Thread();

    /**
     * @brief Destructor
    */
    ~Thread();

    /**
     * @brief Start the thread
    */
    void start();

    /**
     * @brief Exit thread
    */
   void exit();

    /**
     * Callback used to pass as function into pthread_create()
    */
    static void* callback(void *ctx);

    protected:

    /**
     * @brief Run virtual function
    */
    virtual void runFunc() = 0;

    private:

    pthread_t thread; //!< thread ID

  };

}

#endif