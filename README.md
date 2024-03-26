# VastTakeHomeChallenge
Vast Take-Home Coding Excercise March 2024

# Development Environment

This application was developed on a Ubuntu 22.02 Parallels virtual machine.
using g++ 11.4.0.

# Compilation

To compile the code run the following:

`cd VastTakeHomeChallenge$`

`make clean; make`

# Run Application

To run the application using default number of trucks [5] and default number of stations [2], run the following:

`./vastChallenge`

# Exit Application

This application will exit on its own after simulated 72-hours (72 * 100ms = 7.2 sec)
or if user enters `Ctrl-C`.

# Architecture and Design

## Overview

This application is a multithreaded application  composed of `n` number of truck threads and `m` number of unload station thhreads.

Each station will have an associated queue where it will hold truck references ready to unload


## Truck

A truck (see `Truck::Truck` class) is an object thread with the following state machine executed in the thread loop:

```plantuml
@startuml

[*] --> IDLE
IDLE --> IDLE
IDLE : Truck has not been dispatched to a site


IDLE --> LOADING
LOADING --> LOADING
LOADING : Truck is in site being loaded with Helium-3

LOADING --> TRAVELLING_TO_UNLOAD_STATION
TRAVELLING_TO_UNLOAD_STATION --> TRAVELLING_TO_UNLOAD_STATION
TRAVELLING_TO_UNLOAD_STATION: Truck is travelling to unload station

TRAVELLING_TO_UNLOAD_STATION --> UNLOADING
UNLOADING --> UNLOADING
UNLOADING: Truck is unloading Helium-3 at station

UNLOADING --> WAIT_FOR_UNLOAD_DONE
WAIT_FOR_UNLOAD_DONE: Wait for station to signal done unloading truck.

WAIT_FOR_UNLOAD_DONE --> TRAVELLING_TO_SITE
TRAVELLING_TO_SITE --> TRAVELLING_TO_SITE
TRAVELLING_TO_SITE: Truck is travelling back to site

TRAVELLING_TO_SITE --> LOADING

@enduml
```

##  Unloading Station

An unloading station (see `UnloadingStation::UnloadingStation` class) is an object thread with a reference to a queue.  Each thread loop executes the following state machine:


```plantuml
@startuml

[*] --> IDLE
IDLE --> IDLE
IDLE:  Station is not servicing a truck.

IDLE --> UNLOADING
UNLOADING --> UNLOADING
UNLOADING:  Station is unloading the Helium-3 off the truck.

UNLOADING --> DONE
DONE --> IDLE
DONE:  Station is done unloading Helium-3 off the truck, and truck is removed from queue

@enduml
```