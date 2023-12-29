#ifndef PROJ2_AED_AIRLINE_H
#define PROJ2_AED_AIRLINE_H

#include "string"

using namespace std;

class Airline {
private:
    string code;
    string name;
    string callSign;
    string country;
public:
    Airline(string code, string name, string callSign, string country);
    string getCode() const;
    string getName() const;
    string getCallSign() const;
    string getCountry() const;
};
#endif //PROJ2_AED_AIRLINE_H
