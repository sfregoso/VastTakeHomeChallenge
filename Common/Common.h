#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdint.h>
namespace Common{

enum
{
    RUN_FOREVER = 1,
    SIM_ONE_HR_IN_MICROSECONDS = 1000000L, // Simulate 1 hour is 1e6 us (1 sec)
    SIM_ONE_MIN_IN_MICROSECONDS = (SIM_ONE_HR_IN_MICROSECONDS/60), // Simulate 1 min is 1e6/60 us (16667 us ~ 16ms)
    UNKNOWN_ID = -1,
};

      struct OperationTime
      {
        int64_t durationTime; //!< Time in hours to load truck with Helium-3 at Site
        struct timespec startTime; //!< Time when loading started

        void setDurationTime(float durationHrsIn);

        bool durationTimeTranspired();

        void updateStartTime();
      };

}

#endif