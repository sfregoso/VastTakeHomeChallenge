/**
 * @file Utils.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Utils implementation file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include <stdint.h>
#include <stdlib.h> //srand, rand
#include <time.h> //time
#include "Utils.h"
#include "../Common/Common.h"


namespace Utils
{

   void randStart(void) {
      auto seed = time(NULL);
      srand(seed);
   }

    float randSitDurationHrs(void)
    {
        int32_t randNum = (rand() % Common::MAX_SITE_DURATION_HRS) + Common::MIN_SITE_DURATION_HRS;
        //int32_t randNum = 1;
        return (float)randNum;
    }

    enum {
       ONE_SEC_IN_MICROSECONDS = 1000000,
       ONE_MICROSEC_IN_NANOSEC =  1000,
    };

    int64_t compTimespecDiff(struct timespec left, struct timespec right)
    {
    
        return (((int64_t)left.tv_sec - (int64_t)right.tv_sec) * (int64_t)ONE_SEC_IN_MICROSECONDS)
               + (((int64_t)left.tv_nsec - (int64_t)right.tv_nsec) / (int64_t)ONE_MICROSEC_IN_NANOSEC);
    
    }
}