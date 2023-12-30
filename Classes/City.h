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
    string getName() const;
    string getCountry() const;
    vector<string> getAirportCodes() const;

    void addAirportCode(const string& airportCode);
};

#endif //PROJ2_AED_CITY_H
