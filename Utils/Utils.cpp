#include <stdint.h>
#include <stdlib.h> //srand, rand
#include <time.h> //time
#include "Utils.h"


namespace Utils
{

   void randStart(void) {
      auto seed = time(NULL);
      srand(seed);
   }

    float randFlt(void)
    {
        int32_t randNum = (rand() % 5) + 1;
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