#include <unistd.h>
#include <assert.h>
#include "UnloadStation.h"
#include "../Common/Common.h"
#include "../FifoQueue/FifoQueue.h"
namespace UnloadStation
{


    UnloadStation::UnloadStation(uint32_t idIn, void *truckQueueIn)
    : state(UnloadStationState::IDLE)
    , truckQueue(truckQueueIn)
    , id(idIn)
    , waitTimeHrs(0)
    {

    }

    UnloadStation::~UnloadStation()
    {

    }

    void UnloadStation::incWaitTime()
    {
        this->waitTimeHrs += UNLOADING_TIME_HRS;

    }

    void UnloadStation::decWaitTime()
    {
        if(this->waitTimeHrs > 0) {
          this->waitTimeHrs -= UNLOADING_TIME_HRS;
        }

    }

    float UnloadStation::getWaitTime()
    {
        return this->waitTimeHrs;

    }

    void UnloadStation::setWaitTime()
    {

    }

    void UnloadStation::processTruckInQueueIfAny()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        if(!truckQ->empty()) {

            auto id = truckQ->pop()->getId();
            this->decWaitTime();
            printf("Station[%d]:  Processed Truck[%d]\n", this->id, id);

        } 

    }

    void* UnloadStation::getTruckQueue()
    {
        return this->truckQueue;
    }

    void UnloadStation::setId(int32_t idIn)
    {
        this->id = idIn;
    }

    void UnloadStation::addTruckToQueue(void * truckPtr)
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        truckQ->push(reinterpret_cast<Truck::Truck*>(truckPtr));
        this->incWaitTime();
    }

    void UnloadStation::removeTruckFromQueue()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        auto truckId = truckQ->pop()->getId();

        printf("Station[%d]: Removed Truck[%d] from queue.\n", this->id, truckId);

        this->decWaitTime();
    }

    UnloadStation::UnloadStationState UnloadStation::idleState()
    {
        UnloadStationState nextState = this->state;
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        if(!truckQ->empty()) {
            this->unloadingTime.updateStartTime();
            this->unloadingTime.setDurationTime(UNLOADING_TIME_HRS);
            nextState = UnloadStationState::UNLOADING;
        }

        return nextState;

    }

    UnloadStation::UnloadStationState UnloadStation::unloadingState()
    {
        UnloadStationState nextState = this->state;

        if(this->unloadingTime.durationTimeTranspired()) {
            nextState = UnloadStationState::DONE;
        }

        return nextState;
    }

    UnloadStation::UnloadStationState UnloadStation::doneState()
    {
        UnloadStationState nextState = this->state;

        this->decWaitTime();

        return nextState;

    }

    void UnloadStation::setState(UnloadStation::UnloadStationState nextState)
    {
        if(this->state != nextState) {
            printf("Station[%d]:  currentState=%d, NextState=%d\n", this->id, this->state, nextState);
        }

        this->state = nextState;
    }


    void UnloadStation::runFunc()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        while(Common::RUN_FOREVER) {
            UnloadStationState nextState = this->state;

            switch(this->state) {

                case UnloadStationState::IDLE:
                    nextState = this->idleState();
                break;
                case UnloadStation::UNLOADING:
                    nextState = this->unloadingState();
                break;
                case UnloadStationState::DONE:
                    nextState = this->doneState();
                break;
                default:
                    assert(0);

            }

            this->setState(nextState);

            usleep(1000);
        }

    }

}