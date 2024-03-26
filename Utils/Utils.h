/**
 * @file Utils.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Utils header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _UTILS_H_
#define _UTILS_H_

namespace Utils
{
    /**
     * @brief Starting point for generation of random number
    */
    void randStart(void);

    /**
     * @brief Generate random floating number between
    */
    float randSitDurationHrs(void);

    /**
     * @brief Compute difference between timepec variable
     * 
     * @return Return the difference between timespec input arguments
    */
    int64_t compTimespecDiff(struct timespec left, struct timespec right);
}

#endif