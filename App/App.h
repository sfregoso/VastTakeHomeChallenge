/**
 * @file App.h
 * @author Santos F. Fregoso
 * @date 03/25/2024
 * @brief Application header file
 * 
 * @note This software is part of the "Vast Take-Home Coding Excersise" issued on 03/19/2024
*/
#ifndef _APP_H_
#define _APP_H_
#include "../Truck/Truck.h"
#include "../UnloadStation/UnloadStation.h"
#include "../FifoQueue/FifoQueue.h"

namespace App
{

    class App 
    {
        public:
    
        App(uint32_t numTrucks, uint32_t numStations);
    
        ~App();
    
        void Start();

        void Stop();
    
        static constexpr uint32_t MAX_NUM_TRUCKS = 20;
        static constexpr uint32_t MAX_NUM_STATIONS = 20;
    
        private:
    
        uint32_t numTrucks; //!< Number of trucks
        uint32_t numStations; //!< Number of unloading stations
    
        Truck::Truck **trucks; //!< Pointer to array of trucks
        UnloadStation::UnloadStation **stations; //!< Pointer to array of trucks
        FifoQueue::FifoQueue* truckQueue; //!< Queue of trucks
    };

}

#endif
