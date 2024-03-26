/**
 * @file Common.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Common implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include <time.h>
#include "Common.h"
#include "../Utils/Utils.h"

namespace Common {

     void OperationTime::setDurationTime(float durationHrsIn)
     {
         this->durationTimeHrs = durationHrsIn;
         this->durationTimeUs = (int64_t)(durationHrsIn * Common::SIM_ONE_HR_IN_MICROSECONDS);
     }
     
     bool OperationTime::durationTimeTranspired()
     {
       struct timespec now;
       clock_gettime(CLOCK_REALTIME, &now);
   
       int64_t elapsedTimeUs = Utils::compTimespecDiff(now, this->startTime);
   
       return (elapsedTimeUs >= this->durationTimeUs);
     }
   
     void OperationTime::updateStartTime() {
       clock_gettime(CLOCK_REALTIME, &this->startTime);
     }

  }