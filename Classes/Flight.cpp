#include "Flight.h"

Flight::Flight(string d, string a): destCode(d), airlineCode(a) {}

string Flight::getDestCode() const {
    return destCode;
}

string Flight::getAirlineCode() const {
    return airlineCode;
}

