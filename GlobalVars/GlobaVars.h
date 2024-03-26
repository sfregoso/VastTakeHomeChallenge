/**
 * @file GlobalVars.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Global variable header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _GLOBAL_VARS_H
#define _GLOBAL_VARS_H

#include <inttypes.h>

//#ifndef EXTERN 
//#define EXTERN extern
//#endif
extern int32_t exitFlag; //!< Flag used to exit app. Processed by all threads in the app

enum{
    
    DONT_EXIT_APP =  0, //!< Don't exit application
    EXIT_APP = 1, //!< Exit the application
};

#endif