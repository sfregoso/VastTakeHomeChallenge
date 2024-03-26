/**
 * @file FifoQueue.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief FifoQueue implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include "FifoQueue.h"
namespace FifoQueue
{
    FifoQueue::FifoQueue()
    : q()
    , done(false)
    {

    }

    FifoQueue::~FifoQueue()
    {

    }

    void FifoQueue::waitForSignalDone()
    {
        std::unique_lock lk(this->mtx);
        this->cv.wait(lk, [this]{return this->done; });

    }

    Truck::Truck* FifoQueue::pop()
    {
        Truck::Truck* ret = nullptr;

        std::unique_lock lk(this->mtx);

        ret = this->q.front();

        this->q.pop();
        this->done = true;

        lk.unlock();

        this->cv.notify_one();

        return ret;
    }

    Truck::Truck* FifoQueue::front()
    {
        return this->q.front();
    }

    void FifoQueue::push(Truck::Truck * value)
    {
        {
            std::lock_guard lk(this->mtx);

            int val = 0;
            this->q.push(value);
            this->done = false;
            //printf("Truck id=%d.  Queue has %ld items\n", value->getId(), this->q.size());

        }

    }

    bool FifoQueue::empty()
    {
        return this->q.empty();
    }


}