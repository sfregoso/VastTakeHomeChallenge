/**
 * @file UnloadStation.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Unload station header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _UNLOADING_STATION_H_
#define _UNLOADING_STATION_H_

#include <stdint.h>
#include <mutex>
#include <map>
#include "../Thread/Thread.h"
#include "../Common/Common.h"

namespace UnloadStation {


  /**
   * @brief Class representing an unload station as a thread
  */
  class UnloadStation : public Thread::Thread
  {

      public:

      /**
       * @brief State enum of unloading station
      */
      enum UnloadStationState {

        IDLE, //!< UnloadStation not busy (does not have a truck unloading into it)
        UNLOADING, //!< UnloadStation is busy (has a truck unloading into it)
        DONE,

      };

      /**
       * @brief Constructor
       * 
       * @param idIn Station ID
       * @param truckQueueIn  Pointer to Fifo queue used to hold pointers to trucks
      */
      UnloadStation(uint32_t idIn, void *truckQueueIn);

      /**
       * @brief Destructor
      */
      ~UnloadStation();


      /**
       * @brief Return TRUE if stations is busy unloading onto a truck, else FALSE.
      */
      bool busy();

      /**
       * @brief Return the wait time at the station
      */
      float getWaitTime();

      /**
       * @brief Set the ID of the station
       * 
       * @param idIn New ID
      */
      void setId(int32_t idIn);

      /**
       * @brief Add truck pointer to queue
       * 
       * @param truckPtr Generic pointer which later reinterpreted as Truck::Truck
      */
      void addTruckToQueue(void * truckPtr);

      /**
       * @brief Wait for station to signal unload is done.
      */
      void waitForUnloadDone();

      /**
       * @brief Print statistics
      */
     void printStats();


      protected:

      /**
       * @brief Thread function
      */
      void runFunc() override;

      private:

      static constexpr float ONE_MIN_IN_HOURS = (1./60.); //!< One minute in hours 
      static constexpr float UNLOADING_TIME_HRS = (float)(Common::UNLOAD_TIME_MIN) * ONE_MIN_IN_HOURS; //!< Unloading time in hours
  
      private:

      /**
       * @brief Increment the wait time by amount of time it take to unload
      */
      void incWaitTime();

      /**
       * @brief Decrement the wait time by amount of time it take to unload
      */
      void decWaitTime();

      /**
       * @brief Perform IDLE state operations
       * 
       * @return next state
      */
      UnloadStationState idleState();

      /**
       * @brief Perform UNLOADING state operations
       * 
       * @return next state
      */
      UnloadStationState unloadingState();

      /**
       * @brief Perform DONE state operations
       * 
       * @return next state
      */
      UnloadStationState doneState();
      
      /**
       * @brief Set state to next state
       * 
       * @param nextState Next state
      */
      void setState(UnloadStationState nextState);

      /**
       * @brief Remove a truck from the station's queue
      */
      void removeTruckFromQueue();


      private:

      UnloadStationState state;  //!< State
      void *truckQueue; //!< Queue of trucks
      uint32_t id; //!< Identification of the UnloadStation
      float waitTimeHrs; //!< Amount of time trucks will be 
      Common::OperationTime unloadingTime; //!< Unloading time object

      uint32_t totalTrucksServiced;
      std::map<uint32_t, uint32_t> statsTruckUseHash; //Counts the number of times this truck is serviced at a specific station
  
  };


}

#endif