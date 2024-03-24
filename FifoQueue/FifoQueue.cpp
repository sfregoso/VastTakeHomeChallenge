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

    void FifoQueue::push(Truck::Truck * value)
    {
        {
        std::lock_guard lk(this->mtx);

        //std::shared_ptr<Truck::Truck> oneSharedPtr(value, 
        //                           [](Truck::Truck* buff) { delete [] buff; } ); 
        //std::shared_ptr<Truck::Truck> p(value);
        int val = 0;
        //this->q.push(val);
        this->q.push(value);
        this->done = false;
        printf("Truck id=%d.  Queue has %ld items\n", value->getId(), this->q.size());

        //this->cv.notify_one();
        }

    }

    bool FifoQueue::empty()
    {
        return this->q.empty();
    }


}