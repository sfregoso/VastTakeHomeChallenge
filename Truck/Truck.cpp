/**
 * @file Truck.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Truck implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "Truck.h"
#include "../Utils/Utils.h"
#include "../Common/Common.h"
#include "../FifoQueue/FifoQueue.h"
#include "../GlobalVars/GlobaVars.h"

namespace Truck
{

  std::mutex Truck::stationMtx;

  Truck::Truck(uint32_t idIn, UnloadStation::UnloadStation **stationsPtrIn, uint32_t numStationsIn)
  : state(TruckState::IDLE)
  , id(idIn)
  , stations(stationsPtrIn)
  , numStations(numStationsIn)
  , loadingTime()
  {
      // Initialize statistics hash table
      // Key is the ID of the station
      // Value is the number of times this truck visited the station
      for(uint32_t i = 0; i < numStationsIn; i++) {
        this->statsStationUseHash[i] = 0;
      }
  }

  Truck::~Truck()
  {
  }

  void Truck::printStats()
  {
    printf("=================================================\n");
    printf("Statistics for Truck [%d]\n", this->id);
    printf("=================================================\n");
    printf("\tUse of stations by this truck:\n");
    for(auto i = 0; i < this->numStations; i++) {
        printf("\tStation[%d]: %d times\n", i, this->statsStationUseHash[i]);
    }
    printf("\n");

  }

  int32_t Truck::getId()
  {
    return this->id;
  }

  void Truck::setState(TruckState nextState)
  {
    if(nextState != this->state) {
      //printf("Truck[%d]: curState=%d, nextState=%d\n", this->id, this->state, nextState);
    }
    this->state = nextState;
  }

  void Truck::findAvailableOrLowestWaitStation()
  {
    bool allStationsBusy = true;
    float lowestWaitTimeHrs = std::numeric_limits<float>::max();
    uint32_t id = 0; //!< Identification of the UnloadStation

    //First, find station that is not busy
    for(auto i = 0; i < this->numStations; i++) {

       if(!this->stations[i]->busy()) {

          allStationsBusy = false;
          this->lowestWaitStationId = i;

          break;

       } else {
          // Stations is busy. Get its wait time and
          // track which of all is the lowest
          if(this->stations[i]->getWaitTime() < lowestWaitTimeHrs) {

              id = i;
              lowestWaitTimeHrs = this->stations[i]->getWaitTime();
          }
       }

    }

    if(allStationsBusy){

        this->lowestWaitStationId = id;
        printf("ALL STATIONS ARE BUSY: Lowest Wait time is [%.3f] hrs at Station[%d]\n", lowestWaitTimeHrs, this->lowestWaitStationId);

    }


  }


  Truck::TruckState Truck::idleState()
  {
    TruckState nextState = this->state;

    this->loadingTime.updateStartTime();
    this->loadingTime.setDurationTime(Utils::randSitDurationHrs());

    printf("Truck[%d] is loading Helium-3 as site and will take [%.3f] hrs to load ...\n", this->id, this->loadingTime.durationTimeHrs);

    nextState = TruckState::LOADING;

    return nextState;

  }

  Truck::TruckState Truck::loadingState()
  {
    TruckState nextState = this->state;


    if(this->loadingTime.durationTimeTranspired()) {

        //printf("Truck[%d] is done loading and will now travel to station\n", this->id);

        this->travelTime[TravelToLocation::TO_UNLOAD_STATION].updateStartTime();
        this->travelTime[TravelToLocation::TO_UNLOAD_STATION].setDurationTime(TRAVEL_TIME_HRS);

        nextState = TruckState::TRAVELLING_TO_UNLOAD_STATION;

    }

    return nextState;

  }

  Truck::TruckState Truck::travellingState(TravelToLocation toLocation)
  {

    TruckState nextState = this->state;

    switch(toLocation) {

      case TravelToLocation::TO_SITE: {

          if(this->travelTime[toLocation].durationTimeTranspired()) {

              nextState = idleState();
          }


      }
      break;
      case TravelToLocation::TO_UNLOAD_STATION: {

          if(this->travelTime[toLocation].durationTimeTranspired()) {


            nextState = TruckState::UNLOADING;

          }

      }
      break;
      default:
        assert(0);
    }

    return nextState;

  }

  Truck::TruckState Truck::unloadingState()
  {
    TruckState nextState = this->state;

    Truck::stationMtx.lock();

    // Get station ID of first available or with lowest wait time
    this->findAvailableOrLowestWaitStation();

    printf("Truck[%d] has been assigned to Station[%d]\n", this->id, this->lowestWaitStationId);

    // Add this truck to the queue of the station
    this->stations[this->lowestWaitStationId]->addTruckToQueue(this);

    // Increment station use counter for statistics
    this->statsStationUseHash[this->lowestWaitStationId]++;

    Truck::stationMtx.unlock();

    nextState = TruckState::WAIT_FOR_UNLOAD_DONE;

    return nextState;
  }

  Truck::TruckState Truck::waitForUnloadDoneState()
  {
    TruckState nextState = this->state;

    // Blocking wait till station signals done unloading
    this->stations[this->lowestWaitStationId]->waitForUnloadDone();

    printf("Truck[%d]: Unloading done!\n", this->id);

    nextState = TruckState::TRAVELLING_TO_SITE;

    return nextState;
  }


  void Truck::runFunc()
  {

    while(exitFlag == DONT_EXIT_APP) {

       TruckState nextState = this->state;

       switch(this->state) {

        case TruckState::IDLE: {

          nextState = this->idleState();

        }
        break;
        case TruckState::LOADING: {

          nextState = loadingState();

        }
        break;
        case TruckState::TRAVELLING_TO_UNLOAD_STATION: {

          nextState = this->travellingState(TravelToLocation::TO_UNLOAD_STATION);

        }
        break;
        case TruckState::UNLOADING: {

          nextState = this->unloadingState();

        }
        break;
        case TruckState::WAIT_FOR_UNLOAD_DONE: {

          nextState = this->waitForUnloadDoneState();

        }
        break;
        case TruckState::TRAVELLING_TO_SITE: {

          nextState = this->travellingState(TravelToLocation::TO_SITE);

        }
        break;

       }

       this->setState(nextState);

       usleep(10);

    }

  }


}