#include "Airport.h"

#include <set>

Airport::Airport(string code, string name, string cityName, string countryName, double latitude, double longitude): code(code), name(name),
                                                                                          cityName(cityName), countryName(countryName), latitude(latitude), longitude(longitude) {}


string Airport::getCode() const {
    return code;
}


void Airport::setCode(const string &code) {
    this->code = code;
}


bool Airport::isProcessing() const {
    return processing;
}


void Airport::setProcessing(bool p) {
    Airport::processing = p;
}


bool Airport::isVisited() const {
    return visited;
}


int Airport::getNum() const {
    return num;
}


void Airport::setNum(int num) {
    Airport::num = num;
}


int Airport::getLow() const {
    return low;
}


void Airport::setLow(int low) {
    Airport::low = low;
}


void Airport::setVisited(bool v) {
    Airport::visited = v;
}


const vector<Flight> &Airport::getFlights() const {
    return flights;
}

void Airport::addFlight(Flight flight) {
    flights.push_back(flight);
}

string Airport::getName() const {
    return name;
}

string Airport::getCityName() const {
    return cityName;
}

string Airport::getCountryName() const {
    return countryName;
}

double Airport::getLatitude() const {
    return latitude;
}

double Airport::getLongitude() const {
    return longitude;
}

int Airport::getOutDegree() const {
    return flights.size();
}

void Airport::setInDegree(int in) {
    Airport::inDegree = in;
}

int Airport::getInDegree() const{
    return inDegree;
}

int Airport::getNrDifferentAirlines() const {
    set<string> airlines;

    for(auto a: flights){
        airlines.insert(a.getAirlineCode());
    }

    return airlines.size();
}

bool Airport::operator<(Airport b) const{
    return this->flights.size() > b.flights.size();
}

string Airport::getLastAirport() const {
    return lastAirport;
}

void Airport::setLastAirport(const std::string &lastAirport) {
    this->lastAirport = lastAirport;
}

void Airport::increaseInDegree() {
    inDegree++;
}

string Airport::getLastAirline() const {
    return lastAirline;
}

void Airport::setLastAirline(const string &lastAirline) {
    this->lastAirline = lastAirline;
}
