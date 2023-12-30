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
        /**
         * Constructor that receives the flight's destination and airlineCode
         * @param d
         * @param a
        */
        Flight(string d, string a);
        /**
         * @return the flight's destination code
         */
        string getDestCode() const;
        /**
         * @return the flight's airline code
         */
        string getAirlineCode() const;
        void setDest(string dest);

};

#endif //PROJ2_AED_FLIGHT_H
