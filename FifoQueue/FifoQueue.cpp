#include "FifoQueue.h"
namespace FifoQueue
{
    FifoQueue::FifoQueue()
    {

    }

    FifoQueue::~FifoQueue()
    {

    }

    Truck::Truck* FifoQueue::pop()
    {
        Truck::Truck* ret;

        std::unique_lock lk(this->mtx);

        ret = this->q.front();

        this->q.pop();

        lk.unlock();

        return ret;
    }

    void FifoQueue::push(Truck::Truck * value)
    {
        std::unique_lock lk(this->mtx);

        this->q.push(value);
        printf("Truck id=%d.  Queue has %ld items\n", value->getId(), this->q.size());

        lk.unlock();
        this->cv.notify_one();

    }

    bool FifoQueue::empty()
    {
        return this->q.empty();
    }


}