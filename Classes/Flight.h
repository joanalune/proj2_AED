#ifndef PROJ2_AED_FLIGHT_H
#define PROJ2_AED_FLIGHT_H

#include "string"
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Flight{
private:
    Airport origin, destination;
    Airline airline;
};

#endif //PROJ2_AED_FLIGHT_H
