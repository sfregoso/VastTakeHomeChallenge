/**
 * @file UnloadStation.hpp
 * @author Santos F Fregoso
 * @date March 20, 2024
 * @brief 
 * 
*/
#ifndef _UNLOADING_STATION_H_
#define _UNLOADING_STATION_H_

#include <stdint.h>
#include "../Thread/Thread.h"
#include "../Common/Common.h"
//#include "../Truck/Truck.h" //Causes include loop

namespace UnloadStation {



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

      UnloadStation(uint32_t idIn, void *truckQueueIn);

      ~UnloadStation();


      float getWaitTime();

      void setId(int32_t idIn);

      void addTruckToQueue(void * truckPtr);

      void waitForUnloadDone();

      static constexpr float ONE_MIN_IN_HOURS = (1./60.); // 30 min;
      static constexpr float UNLOADING_TIME_HRS = 5 * ONE_MIN_IN_HOURS; // 5 minutes in hours;

      protected:

      void runFunc() override;
  
      private:

      void *getTruckQueue();

      void setWaitTime();

      void incWaitTime();
      void decWaitTime();

      UnloadStationState idleState();
      UnloadStationState unloadingState();
      UnloadStationState doneState();

      void removeTruckFromQueue();

      void setState(UnloadStationState nextState);

      private:

      UnloadStationState state;  //!< State
      void *truckQueue; //!< Queue of trucks
      uint32_t id; //!< Identification of the UnloadStation
      float waitTimeHrs; //!< Amount of time trucks will be 
      Common::OperationTime unloadingTime;
  
  };

}

//#include "UnloadStation_impl.h"

#endif