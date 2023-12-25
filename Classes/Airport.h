#ifndef PROJ2_AED_AIRPORT_H
#define PROJ2_AED_AIRPORT_H

#include "string"
#include "City.h"

using namespace std;

class Airport{
private:
    string code;
    string name;
    City city;
    double latitude;
    double longitude;
};

#endif //PROJ2_AED_AIRPORT_H
