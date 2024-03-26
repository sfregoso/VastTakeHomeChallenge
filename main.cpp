/**
 * @file main.cpp
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Main
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#include <iostream>
#include <assert.h>
#include <unistd.h>
#include <signal.h>
#include "App/App.h"
#include "Common/Common.h"
//#define EXTERN
#include "GlobalVars/GlobaVars.h"

//!< Global variable used to exit all threads.
int32_t exitFlag = DONT_EXIT_APP;

/**
 *  @brief Signal handler that when called raises flag to exit threads.
 */
void CtrlHandler(int dummy) {

    // Raise flag to exit the application threads
    exitFlag = EXIT_APP;
}

/**
 * @brief Print usage of application
*/
void usage(char *progName)
{
    printf("\nUsage:  %s [-m numStations] [-n numTrucks]\n\n", progName);
}

/**
 * @brief Main entry of application
 * 
 * @param argc Number of arguments entered in application
 * @param argv Command line argument entries
*/
int main(int argc, char *argv[])
{

    uint32_t numTrucks = Common::DEFAULT_NUM_TRUCKS;
    uint32_t numStations = Common::DEFAULT_NUM_STATIONS;
    int opt;

    // Parse options if an argument is entered, else use default values
    if(argc > 1) {

       while((opt = getopt(argc, argv, "m:n:")) != -1) {
   
           switch(opt) {
               case 'm':
                   numStations = atoi(optarg);
               break;
               case 'n':
                   numTrucks = atoi(optarg);
               break;
               default:
                    usage(argv[0]);
                    return EXIT_FAILURE;
           }
        }

    }

    // Validate range of number of trucks
    if( (numTrucks < Common::MIN_NUM_TRUCKS) || (numTrucks > Common::MAX_NUM_TRUCKS) ) {
        printf("Error.  Number of trucks [%d] out of range [%d, %d]\n", numTrucks, Common::MIN_NUM_TRUCKS, Common::MAX_NUM_TRUCKS);
        return EXIT_FAILURE;
    }

    // Validate range of number of unload stations
    if( (numStations < Common::MIN_NUM_STATIONS) || (numStations > Common::MAX_NUM_STATIONS) ) {
        printf("Error.  Number of stations [%d] out of range [%d, %d]\n", numStations, Common::MIN_NUM_STATIONS, Common::MAX_NUM_STATIONS);
        return EXIT_FAILURE;
    }

    // Setup signal handler to capture Ctrl-C to end application
    signal(SIGINT, CtrlHandler);

    printf("Main():  numTrucks = %d, numStations = %d\n", numTrucks, numStations);

    // Create app
    App::App app(numTrucks, numStations);

    // Start the app
    app.Start();

    uint32_t hourCount = 0; // simulated count of hours

    // Run for the simulated 72 hours
    while((hourCount < Common::SIMULATION_DURATION_HRS) &&
           (exitFlag == DONT_EXIT_APP)) {

        usleep(Common::SIM_ONE_HR_IN_MICROSECONDS);

        hourCount++;

    }

    app.Stop();

    //Print out status

    return EXIT_SUCCESS;
}