#ifndef PROJ2_AED_FILEREADER_H
#define PROJ2_AED_FILEREADER_H

#include <unordered_map>
#include "Airport.h"

class FileReader{
private:
    void readAirlines();
    void readAirports();
    void readFlights();
public:

    unordered_map <int, Airline*> airlines;
    unordered_map <int, Airport*> airports;


};

#endif //PROJ2_AED_FILEREADER_H
