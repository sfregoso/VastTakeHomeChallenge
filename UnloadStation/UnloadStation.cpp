/**
 * @file UnloadStation.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Unload station implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include <unistd.h>
#include <assert.h>
#include "UnloadStation.h"
#include "../Common/Common.h"
#include "../FifoQueue/FifoQueue.h"
#include "../GlobalVars/GlobaVars.h"

namespace UnloadStation
{

    UnloadStation::UnloadStation(uint32_t idIn, void *truckQueueIn)
    : state(UnloadStationState::IDLE)
    , truckQueue(truckQueueIn)
    , id(idIn)
    , waitTimeHrs(0)
    , unloadingTime()
    , totalTrucksServiced(0)
    {
    }

    UnloadStation::~UnloadStation()
    {
    }

    void UnloadStation::printStats()
    {
        printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        printf("Statistics for Station [%d]\n", this->id);
        printf("&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&&\n");
        printf("\tTotal Trucks serviced here: %d\n", this->totalTrucksServiced);
        for(auto i = 0; i < this->statsTruckUseHash.size(); i++) {
            printf("\tTruck[%d] used this station %d times  - %.2f%%\n", i, this->statsTruckUseHash[i], (float)this->statsTruckUseHash[i]/this->totalTrucksServiced*100.);
        }

    }

    bool UnloadStation::busy()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        return (!truckQ->empty());
    }

    void UnloadStation::incWaitTime()
    {
        this->waitTimeHrs += UNLOADING_TIME_HRS;

    }

    void UnloadStation::decWaitTime()
    {
        this->waitTimeHrs -= UNLOADING_TIME_HRS;

        if(this->waitTimeHrs < 0) {
            this->waitTimeHrs = 0;
        }

    }

    float UnloadStation::getWaitTime()
    {
        return this->waitTimeHrs;

    }

    void UnloadStation::setId(int32_t idIn)
    {
        this->id = idIn;
    }

    void UnloadStation::addTruckToQueue(void * truckPtr)
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);
        Truck::Truck* truckP = reinterpret_cast<Truck::Truck*>(truckPtr);

        // Push the truck pointer into the station's queue
        truckQ->push(reinterpret_cast<Truck::Truck*>(truckPtr));

        // Increment the wait time at this station
        this->incWaitTime();

        // For statistics, increment the number of time this truck used this station
        statsTruckUseHash[truckP->getId()]++;

        printf("Station[%d]: Added Truck[%d] from queue. Wait time is now [%.3f] hrs\n", this->id, truckQ->front()->getId(), this->getWaitTime());
    }

    void UnloadStation::removeTruckFromQueue()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        auto truckId = truckQ->pop()->getId();


        this->decWaitTime();
        printf("Station[%d]: Removed Truck[%d] from queue. Wait time is now [%.3f] hrs\n", this->id, truckId, this->getWaitTime());

    }

    void UnloadStation::waitForUnloadDone()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        // Blocking wait for done signal
        truckQ->waitForSignalDone();
    }

    UnloadStation::UnloadStationState UnloadStation::idleState()
    {
        UnloadStationState nextState = this->state;
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        // If truck has been added to the queue
        if(!truckQ->empty()) {

            // Set time values to compute elapsed time
            this->unloadingTime.updateStartTime();
            this->unloadingTime.setDurationTime(UNLOADING_TIME_HRS);

            nextState = UnloadStationState::UNLOADING;

            printf("Station[%d] is now servicing Truck[%d]\n", this->id, truckQ->front()->getId());
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

        // Remove the truck from the queue
        this->removeTruckFromQueue();

        // For statistic, incremented the service counter
        this->totalTrucksServiced++;

        nextState = UnloadStationState::IDLE;

        return nextState;

    }

    void UnloadStation::setState(UnloadStation::UnloadStationState nextState)
    {
        if(this->state != nextState) {
            //printf("Station[%d]:  currentState=%d, NextState=%d\n", this->id, this->state, nextState);
        }

        this->state = nextState;
    }


    void UnloadStation::runFunc()
    {
        FifoQueue::FifoQueue* truckQ = reinterpret_cast<FifoQueue::FifoQueue *>(this->truckQueue);

        //while(Common::RUN_FOREVER) {
        while(exitFlag == DONT_EXIT_APP) {
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

            usleep(10);
        }

    }

}