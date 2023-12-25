
#ifndef PROJ2_AED_CITY_H
#define PROJ2_AED_CITY_H

#include <string>

using namespace std;

class City{
private:
    string name;
    string country;
public:
    City(string name, string country);
    string getName();
    string getCountry();
};

#endif //PROJ2_AED_CITY_H
