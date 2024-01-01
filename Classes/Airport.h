#ifndef PROJ2_AED_AIRPORT_H
#define PROJ2_AED_AIRPORT_H


#include <vector>
#include "City.h"
#include "Flight.h"

class Airport {
    string code;                // contents
    string name;
    string cityName;
    string countryName;
    double latitude;
    double longitude;

    vector<Flight> flights;  // list of outgoing flights

    bool visited;          // auxiliary field
    bool processing;       // auxiliary field
    int num;               // auxiliary field
    int low;               // auxiliary field
    string lastAirport;    // auxiliary field; stores key to airport visited previously in bfs
    string lastAirline;    //
    int inDegree=0;




public:
    /**
     * Constructor that receives the airport's code, name, cityname, countryname, latitude and longitude
     * @param airportCode
     * @param name
     * @param cityName
     * @param countryName
     * @param latitude
     * @param longitude
     */
    Airport(string airportCode, string name, string cityName, string countryName, double latitude, double longitude);
    /**
     * @return the airport's name
     */
    string getName() const;
    /**
     * @return the airport's code
     */
    string getCode() const;
    /**
     * @return the airport's city name
     */
    string getCityName() const;
    /**
     * @return the airport's country name
     */
    string getCountryName() const;
    /**
     * @return the airport's latitude
     */
    double getLatitude() const;
    /**
     * @return the airport's longitude
     */
    double getLongitude() const;

    void setCode(const string &code);
    void setName(const string &name);
    void setCity(const City &city);
    /**
     * Checks if the airport is visited
     * @return true if the airport is visited, false if it's not
     */
    bool isVisited() const;
    /**
     * Sets the airport's visited status to given bool
     * @param v
     */
    void setVisited(bool v);
    /**
     * Checks if the airport is being processed
     * @return true if the airport is visited, false if it's not
     */
    bool isProcessing() const;
    /**
     * Sets the airport's processing status to given bool
     * @param v
     */
    void setProcessing(bool p);
    /**
    * @return a vector of all the airport's outgoing flights
    */
    const vector<Flight> &getFlights() const;
    /**
    * Adds a flight to the airport's outgoing flights vector
    * @param flight
    */
    void addFlight(Flight flight);
    bool removeEdgeTo(Airport *d);
    /**
     * @return the number of outgoing flights
     */
    int getOutDegree() const;
    /**
     * @return the number of different airlines doing the airport's outgoing flights
     * @details Time complexity: O(n) * O(log(i)), n being the size of the flights vector and i being the size of the set airlines created in the function
     */
    int getNrDifferentAirlines() const;
    /**
     * @return the code of the airport visited prior to the current one in a dfs search
     */
    string getLastAirport() const;
    /**
     * sets lastAirport field to given airport code
     * @param lastAirport
     */
    void setLastAirport(const string& lastAirport);
    /**
     * @return the code of the airline of last incoming flight to the current airport in a dfs
     */
    string getLastAirline() const;
    /**
     * sets lastAirline field to given airline code
     * @param lastAirline
     */
    void setLastAirline(const string& lastAirline);
    void setInDegree(int inDegree);
    /**
     * @return the number of incoming flights
     */
    int getInDegree() const;
    /**
     * Increases the number of incoming flights by one
     */
    void increaseInDegree();
    /**
     * @return num field
     */
    int getNum() const;
    /**
     * @return low field
     */
    int getLow() const;
    /**
     * sets num field to given int
     * @param num
     */
    void setNum(int num);
    /**
     * sets low field to given int
     * @param low
     */
    void setLow(int low);
    /**
     * Less operator overload so that airports are compared by the sum of their outgoing flights and incoming flights
     * @param b
     */
    bool operator<(Airport b) const;

    friend class Graph;

};


#endif //PROJ2_AED_AIRPORT_H
