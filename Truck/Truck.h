/**
 * @file Truck.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Truck header file
 * 
 * 
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _TRUCK_H_
#define _TRUCK_H_

#include <stdint.h>
#include <unistd.h>
#include <map>
#include "../Thread/Thread.h"
#include "../UnloadStation/UnloadStation.h"
#include "../Common/Common.h"

namespace Truck {

  /**
   * @brief Truck Class
  */
  class Truck : public Thread::Thread
  {
      static std::mutex stationMtx; //!< Mutex to protect assigning station to truck

      public:

      /**
       * @brief Truck constructor
      */
      Truck(uint32_t idIn, UnloadStation::UnloadStation **stationsPtrIn, uint32_t numStationsIn);

      /**
       * @brief Truck destructor
      */
      ~Truck();

      /**
       * @brief Return the ID of the truck.
      */
      int32_t getId();

      void printStats();


      protected:

      /**
       * @brief Thread function
      */
      void runFunc() override;

      private:

      static constexpr float ONE_MIN_IN_HOURS = (1./60.); //!< One minute in hours 
      static constexpr float TRAVEL_TIME_HRS = (float)(Common::TRAVEL_TIME_MIN) * ONE_MIN_IN_HOURS; //!< The amount of time in hours it takes for the truck to travel from site to/from unload station
      static constexpr bool STATION_NOT_FOUND = false; //!< Bool state representing if an unload station has NOT been found
      static constexpr bool STATION_FOUND = true; //!< Bool state representing if an unload station has been found.

      private:

      /**
       * @brief Truck state enum
      */
      enum TruckState {

        IDLE, //!< Truck has not been dispatch and is doing nothing
        LOADING, //!< Truck is at site loading Helium-3
        TRAVELLING_TO_UNLOAD_STATION, //!< Truck is traveling from site to unloading station
        UNLOADING, //!< Truck is unloading at the unloading station
        WAIT_FOR_UNLOAD_DONE, //!< Truck is waiting for unloading operation to complete (signaled by unload station)
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

      private:

      /**
       * @brief Find the first unbusy station or if all busy then the one with lowest wait time.
      */
      void findAvailableOrLowestWaitStation();

      /**
       * @brief Set the truck state to the input state
      */
      void setState(TruckState nextState);

      /**
       * @brief Performs IDLE state operations
      */
      TruckState idleState();

      /**
       * @brief Performs LOADING state operations
      */
      TruckState loadingState();

      /**
       * @brief Performs TRAVELLING state operations
       * 
       * @param toLocation Indicates whether travelling to a site or to an unload station
      */
      TruckState travellingState(TravelToLocation toLocation);

      /**
       * @brief Performs UNLOADING state operations
      */
      TruckState unloadingState();

      /**
       * @brief Wait for signal from station indicating that unloading has completed
      */
      TruckState waitForUnloadDoneState();


      private:

      TruckState state;  //!< State
      uint32_t id; //!< Identification of the truck

      UnloadStation::UnloadStation **stations; //!< Pointer to array of stations (allocated outside this class)
      uint32_t numStations; //!< Number of stations
      uint32_t lowestWaitStationId; //!< ID of lowest wait stations

      Common::OperationTime loadingTime; //!< Loading time object
      Common::OperationTime travelTime[TravelToLocation::NUM_TRAVEL_TO_LOCATIONS]; //!< Travel time object

      std::map<uint32_t, uint32_t> statsStationUseHash; //Counts the number of times this truck is serviced at a specific station

  };



}


#endif