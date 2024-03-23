#include <iostream>
#include "../App/App.h"
#include "../Truck/Truck.h"
#include "../Utils/Utils.h"
#include "../UnloadStation/UnloadStation.h"


namespace App
{

    App::App(uint32_t numTrucksIn, uint32_t numStationsIn)
    : numTrucks(numTrucksIn)
    , numStations(numStationsIn)
    {
        // Clamp number of trucks to maximum if input value exceeds maximum
        if(numTrucksIn > MAX_NUM_TRUCKS) {
            std::cout << "Number of trucks[" << numTrucksIn << "] exceeds maximum[" << MAX_NUM_TRUCKS << "].  Setting number to maximum.";
            this->numTrucks = MAX_NUM_TRUCKS;
        }
    
        // Clamp number of stations to maximum if input value exceeds maximum
        if(numStationsIn > MAX_NUM_STATIONS) {
            std::cout << "Number of stations[" << numStationsIn << "] exceeds maximum[" << MAX_NUM_STATIONS << "].  Setting number to maximum.";
            this->numStations = MAX_NUM_STATIONS;
        }
    
        Utils::randStart();

        this->truckQueue = new FifoQueue::FifoQueue[this->numStations];

        // Create array of stations
        this->stations = new UnloadStation::UnloadStation*[this->numStations];
        for(auto i = 0; i < this->numStations; i++) {
            this->stations[i] = new UnloadStation::UnloadStation(i, &this->truckQueue[i]);
        }

        // Create array of trucks
        this->trucks = new Truck::Truck*[this->numTrucks];

        for(auto i = 0; i < this->numTrucks; i++) {
            this->trucks[i] = new Truck::Truck(i, this->stations, this->numStations);
        }
    
    }
    
    App::~App()
    {
        delete [] this->trucks;
        delete [] this->stations;
    }
    
    void App::Start()
    {

        for(auto i = 0; i < this->numStations; i++) {
            this->stations[i]->start();
        }

        for(auto i = 0; i < this->numTrucks; i++) {
            this->trucks[i]->start();
        }
    
    }

}