#ifndef PROJ2_AED_FLIGHT_H
#define PROJ2_AED_FLIGHT_H

#include "string"
#include "Airport.h"
#include "Airline.h"

using namespace std;

class Flight{
    private:
    Airport* dest;
    Airline* airline;
    public:
        Flight(Airport* d, Airline* a);
        Airport* getDest() const;
        Airline* getAirline() const;
        void setDest(Airport* dest);

};

#endif //PROJ2_AED_FLIGHT_H
