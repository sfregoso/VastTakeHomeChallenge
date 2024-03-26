/**
 * @file Common.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Common header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _COMMON_H_
#define _COMMON_H_
#include <stdint.h>
namespace Common {

/**
 * @brief Constants used in the application
*/
enum
{
    RUN_FOREVER = 1, //!< Value used in while loop condition to run forever
    SIM_ONE_HR_IN_MICROSECONDS = 100000L,  //!< Simulate 1 hour is 1e5 us (100 ms)
    SIM_ONE_MIN_IN_MICROSECONDS = (SIM_ONE_HR_IN_MICROSECONDS/60),  //!< Simulate 1 min is 1e5/60 us (1666 us ~ 1.67ms)
    SIMULATION_DURATION_HRS = 72, //!< Per Simulation requirements, simulation duration is to be 72 hours
};

/**
 * @brief Time in minutes of some operations
*/
enum 
{
    TRAVEL_TIME_MIN = 30, //!< Travel time between a mining site and an unload station in minutes
    UNLOAD_TIME_MIN = 5, //!< Time in minutes to unload mined Helium-3 at an unload station
    MIN_SITE_DURATION_HRS = 1, //!< Minimum duration a truck takes at a site to load
    MAX_SITE_DURATION_HRS = 5, //!< Maximum duration a truck takes at a site to load
};

/**
 * @brief Number of truck and station constants
*/
enum {

    DEFAULT_NUM_TRUCKS = 5,  //!< Default number of trucks
    DEFAULT_NUM_STATIONS = 2,  //!< Default number of unload stations
    MIN_NUM_TRUCKS = 1,  //!< Minimum number of trucks
    MIN_NUM_STATIONS = 1,  //!< Minimum number of unload stations
    MAX_NUM_TRUCKS = 25,  //!< Maximum number of trucks
    MAX_NUM_STATIONS = 20,  //!< Maximum number of stations

};

/**
 * Struct used for computing elapsed time during an operation (example: amount of time to load Helimum-3 at a site)
*/
struct OperationTime
{
    int64_t durationTimeUs; //!< Time in us
    float durationTimeHrs; //!< Duration in hours
    struct timespec startTime; //!< Time when loading started

    /**
     * @brief Set the duration (us) from the input duration in hours
     * 
     * Convert the input duration in hours which is simulated and converted to its equivalent 
     * duration in microseconds
     * 
     * @param durationHrsIn Duration in hours
    */
    void setDurationTime(float durationHrsIn);

    /**
     * @brief Return TRUE if duration time has transpired, else FALSE
     * 
     * Gets the difference between now time and the startTime and if exceeds the `durationTimeUs`
     * then TRUE, else FALSE
     * 
     * @return Whether duration time has transpired
     * @retval true Duration time has transpired
     * @retval false Duration time has not transpired
    */
    bool durationTimeTranspired();

    /**
     * @brief Set the startTime to latest clock time
    */
    void updateStartTime();
};

}

#endif