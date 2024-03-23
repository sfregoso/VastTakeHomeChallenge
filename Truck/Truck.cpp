#include <iostream>
#include <unistd.h>
#include <assert.h>
#include "Truck.h"
#include "../Utils/Utils.h"
#include "../Common/Common.h"
#include "../FifoQueue/FifoQueue.h"

namespace Truck
{



  //Truck::Truck(void *stationTruckQueueIn, uint32_t numStationsIn)
  Truck::Truck(uint32_t idIn, UnloadStation::UnloadStation **stationsPtrIn, uint32_t numStationsIn)
  : state(TruckState::IDLE)
  , id(idIn)
  , stations(stationsPtrIn)
  , numStations(numStationsIn)
  , loadingTime()
  {
  }

  Truck::~Truck()
  {
  }

  void Truck::setId(int32_t idIn)
  {
    assert(idIn >= 0);
    this->id = idIn;
  }

  int32_t Truck::getId()
  {
    return this->id;
  }

  void Truck::setState(TruckState nextState)
  {
    if(nextState != this->state) {
      printf("Truck[%d]: curState=%d, nextState=%d\n", this->id, this->state, nextState);
    }
    this->state = nextState;
  }


  Truck::TruckState Truck::idleState(const float& timeTick)
  {
    TruckState nextState = this->state;

    this->loadingTime.updateStartTime();
    this->loadingTime.setDurationTime(Utils::randFlt());

    nextState = TruckState::LOADING;

    return nextState;

  }

  Truck::TruckState Truck::loadingState(const float& timeTick)
  {
    TruckState nextState = this->state;


    if(this->loadingTime.durationTimeTranspired()) {

        
        this->travelTime[TravelToLocation::TO_UNLOAD_STATION].updateStartTime();
        this->travelTime[TravelToLocation::TO_UNLOAD_STATION].setDurationTime(TRAVEL_TIME_HRS);

        nextState = TruckState::TRAVELLING_TO_UNLOAD_STATION;

    }

    return nextState;

  }

  Truck::TruckState Truck::travellingState(TravelToLocation toLocation, const float& timeTick)
  {

    TruckState nextState = this->state;

    switch(toLocation) {

      case TravelToLocation::TO_SITE: {

          if(this->travelTime[toLocation].durationTimeTranspired()) {

              this->loadingTime.updateStartTime();
              this->loadingTime.setDurationTime(Utils::randFlt());
          }

          nextState = TruckState::LOADING;

      }
      break;
      case TravelToLocation::TO_UNLOAD_STATION: {

          if(this->travelTime[toLocation].durationTimeTranspired()) {

            this->unloadingTime.updateStartTime();
            this->unloadingTime.setDurationTime(UNLOADING_TIME_HRS);

            nextState = TruckState::UNLOADING;

          }

      }
      break;
      default:
        assert(0);
    }

    return nextState;

  }

  Truck::TruckState Truck::unloadingState(const float& timeTick)
  {
    TruckState nextState = this->state;

    this->stations[0]->addTruckToQueue(this);

    nextState = TruckState::WAIT_FOR_UNLOAD_DONE;

    return nextState;
  }

  Truck::TruckState Truck::waitForUnloadDoneState(const float& timeTick)
  {
    TruckState nextState = this->state;

    nextState = TruckState::TRAVELLING_TO_SITE;

    return nextState;
  }


  void Truck::runFunc()
  {
    auto timeTick = 0;

    while(Common::RUN_FOREVER) {

       TruckState nextState = this->state;

       switch(this->state) {

        case TruckState::IDLE: {

          nextState = this->idleState(timeTick);

        }
        break;
        case TruckState::LOADING: {

          nextState = loadingState(timeTick);

        }
        break;
        case TruckState::TRAVELLING_TO_UNLOAD_STATION: {

          nextState = this->travellingState(TravelToLocation::TO_UNLOAD_STATION, timeTick);

        }
        break;
        case TruckState::UNLOADING: {

          nextState = this->unloadingState(timeTick);

        }
        break;
        case TruckState::WAIT_FOR_UNLOAD_DONE: {

          nextState = this->waitForUnloadDoneState(timeTick);
        }
        break;
        case TruckState::TRAVELLING_TO_SITE: {

          nextState = this->travellingState(TravelToLocation::TO_SITE, timeTick);

        }
        break;

       }

       this->setState(nextState);

       timeTick++;

       usleep(1000);

    }

  }


}