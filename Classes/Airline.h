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
    /**
     * Constructor that receives the airline code, name, callsign and country
     * @param code
     * @param name
     * @param callSign
     * @param country
     */
    Airline(string code, string name, string callSign, string country);
    /**
     * @return the airline's code
     */
    string getCode() const;
    /**
     * @return the airline's name
     */
    string getName() const;
    /**
     * @return the airline's callsign
     */
    string getCallSign() const;
    /**
     * @return the airline's country
     */
     string getCountry() const;
};
#endif //PROJ2_AED_AIRLINE_H
