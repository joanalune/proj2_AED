#ifndef PROJ2_AED_CITY_H
#define PROJ2_AED_CITY_H

#include <string>
#include <vector>

using namespace std;

class City{
private:
    string name;
    string country;
    vector<string> airportCodes;
public:
    City(string name, string country);
    string getName();
    string getCountry();
    vector<string> getAirportCodes();

    void addAirportCode(const string& airportCode);
};

#endif //PROJ2_AED_CITY_H
