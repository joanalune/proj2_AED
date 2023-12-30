#include "City.h"
#include "Airport.h"


City::City(string name, string country): name(name), country(country) {}

string City::getName() const {
    return name;
}

string City::getCountry() const {
    return country;
}

void City::addAirportCode(const string &airportCode) {
    airportCodes.push_back(airportCode);
}

vector<string> City::getAirportCodes() const {
    return airportCodes;
}

