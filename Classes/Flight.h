#ifndef PROJ2_AED_FLIGHT_H
#define PROJ2_AED_FLIGHT_H

#include "string"
#include "Airline.h"

using namespace std;

class Flight{
    private:
    string destCode;
    string airlineCode;
    public:
        Flight(string d, string a);
        string getDestCode() const;
        string getAirlineCode() const;
        void setDest(string dest);

};

#endif //PROJ2_AED_FLIGHT_H
