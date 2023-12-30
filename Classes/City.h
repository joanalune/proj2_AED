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
    /**
     * Constructor that receives the city's name and country
     * @param name
     * @param country
     */
    City(string name, string country);
    /**
     * @return the city's name
     */
    string getName() const;
    /**
     * @return the city's country
     */
    string getCountry() const;
    /**
     * @return a vector of codes of all airports located in the city
     */
    vector<string> getAirportCodes() const;
    /**
     * Adds an airport code to the airportCodes vector
     * @param airportCode
     */
    void addAirportCode(const string& airportCode);
};

#endif //PROJ2_AED_CITY_H
