/**
 * @file Truck.hpp
 * @author Santos F Fregoso
 * @date March 20, 2024
 * @brief 
 * 
*/
#ifndef _TRUCK_H_
#define _TRUCK_H_

#include <stdint.h>
#include <unistd.h>
#include "../Thread/Thread.h"
#include "../UnloadStation/UnloadStation.h"
#include "../Common/Common.h"
//#include "../FifoQueue/FifoQueue.h"

namespace Truck {

  class TruckThread
  {
    public:

    TruckThread();

    void start();

    static void* callback(void *ctx);

    protected:

    virtual void truckingFunc() = 0;

    private:

    pthread_t thread;


  };

  /**
   * @brief Truck Class
  */
  class Truck : public Thread::Thread
  {
      public:

      /**
       * @brief Truck constructor
      */
      Truck(uint32_t idIn, UnloadStation::UnloadStation **stationsPtrIn, uint32_t numStationsIn);

      /**
       * @brief Truck destructor
      */
      ~Truck();

      void setId(int32_t id);
      int32_t getId();


      /**
       * @brief Truck state enum
      */
      enum TruckState {

        IDLE, //!< Truck has not been dispatch and is doing nothing
        LOADING, //!< Truck is at site loading Helium-3
        TRAVELLING_TO_UNLOAD_STATION, //!< Truck is traveling from site to unloading station
        UNLOADING, //!< Truck is unloading at the unloading station
        WAIT_FOR_UNLOAD_DONE,
        TRAVELLING_TO_SITE, //!< Truck is traveling from unloading station to site

      };

      /**
       * @brief Enum representing locations where trucks travel to
      */
      enum TravelToLocation {
        TO_SITE, //!< Travelling to site
        TO_UNLOAD_STATION, //!< Unloading station
        NUM_TRAVEL_TO_LOCATIONS, //!< Unloading station
      };

      /**
       * @brief
      */
      void setState(TruckState nextState);

      void setLoadingTime(float newLoadingTime);

      //static constexpr float TRAVEL_TIME_MIN = 30 * SIM_ONE_MIN_IN_MICROSECONDS; //;
      //static constexpr float UNLOADING_TIME_MIN = 5 * SIM_ONE_MIN_IN_MICROSECONDS; //;

      static constexpr float ONE_MIN_IN_HOURS = (1./60.); // 30 min;
      static constexpr float TRAVEL_TIME_HRS = 30 * ONE_MIN_IN_HOURS; // 30 min;
      static constexpr float UNLOADING_TIME_HRS = 5 * ONE_MIN_IN_HOURS; // 5 minutes in hours;

      protected:

      void runFunc() override;

      private:

      TruckState idleState(const float& timeTick);
      TruckState loadingState(const float& timeTick);
      TruckState travellingState(TravelToLocation toLocation, const float& timeTick);
      TruckState unloadingState(const float& timeTick);
      TruckState waitForUnloadDoneState(const float& timeTick);


      private:

      TruckState state;  //!< State
      uint32_t id; //!< Identification of the truck

      //void *stationTruckQueue;
      UnloadStation::UnloadStation **stations;
      uint32_t numStations;

      Common::OperationTime loadingTime;
      Common::OperationTime travelTime[TravelToLocation::NUM_TRAVEL_TO_LOCATIONS];
      Common::OperationTime unloadingTime;


  };



}


#endif