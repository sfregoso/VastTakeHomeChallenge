#include <time.h>
#include "Common.h"
#include "../Utils/Utils.h"

namespace Common {

     void OperationTime::setDurationTime(float durationHrsIn)
     {
         this->durationTime = (int64_t)(durationHrsIn * Common::SIM_ONE_HR_IN_MICROSECONDS);
     }
     
     bool OperationTime::durationTimeTranspired()
     {
       struct timespec now;
       clock_gettime(CLOCK_REALTIME, &now);
   
       int64_t elapsedTime = Utils::compTimespecDiff(now, this->startTime);
   
       return (elapsedTime >= this->durationTime);
     }
   
     void OperationTime::updateStartTime() {
       clock_gettime(CLOCK_REALTIME, &this->startTime);
     }

  }