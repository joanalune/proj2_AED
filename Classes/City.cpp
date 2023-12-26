//
// Created by joana on 25-12-2023.
//
#include "City.h"

City::City(string name, string country): name(name), country(country) {}

string City::getName() {
    return name;
}

string City::getCountry() {
    return country;
}

void City::addAirportCode(const string &airportCode) {
    airportCodes.push_back(airportCode);
}

vector<string> City::getAirportCodes() {
    return airportCodes;
}

