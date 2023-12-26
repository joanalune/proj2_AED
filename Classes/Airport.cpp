//
// Created by ebaltazar on 25-12-2023.
//

#include "Airport.h"


Airport::Airport(string code, string name, City city, double latitude, double longitude): code(code), name(name),
                                                                                          city(city), latitude(latitude), longitude(longitude) {}


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


int Airport::getIndegree() const {
    return indegree;
}


void Airport::setIndegree(int indegree) {
    Airport::indegree = indegree;
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


