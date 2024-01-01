#ifndef PROJ2_AED_GRAPH_H
#define PROJ2_AED_GRAPH_H


#include "Airport.h"
#include "City.h"

#include <cstring>
#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <set>
#include <list>
#include <unordered_map>
#include <unordered_set>

using namespace std;

struct filter {
    int type;         // 0 - no filter; 1 - whitelist; 2 - blacklist; 3 - minimize airline changes. 1 and 2 are handled in getBestTrips (Graph class), 3 is handled in printBestFlights (Menu class)
    set<string> codes;
};

class Graph {
    unordered_map<int, Airport> airportTable;
    unordered_map<int, City> cityTable;
    unordered_map<int, Airline> airlineTable;


public:
    /**
     * Default constructor
     */
    Graph();
    /**
     * @return the global number of airports
     */
    int getNumAirport() const;
    /**
     * @return the global number of flights
     */
    int getNumFlights() const;
    /**
     * ?????????????
     * @param diameter
     * @return a vector with pairs (source, destination) of graph diameter and places diameter in diameter
     * @details Time complexity:
     */
    vector<pair<string, string>> getMaximumTrip(int &diameter);
    /**
     * ??????????????????'
     * @param source
     * @param stops
     * @return a vector with the farthest airports from given source
     * @details Time complexity:
     */
    vector<string> farthestAirportsFrom(const string& source, int &stops);
    /**
     * Creates a set of all airports ordered by flight capacity (incoming + outgoing)
     * @return a set of all the airports ordered by flight capacity
     * @details Time complexity: O(n * log(n)), n being the number of airports in the airportsTable hash table
     */
    set<Airport> topAirports();
    /**
     * Creates a set of all the airports essential for the flight system
     * @return a set of all the essential airports
     * @details Time complexity:
     */
    unordered_set<string> essentialAirports();
    /**
     * Takes the user input and places the airport codes near the input in a vector, for example, if the user inputs coordinates, the function
     * will return the nearest airport(s), or if the user inputs a city, a vector of the codes of the airports inside that city is returned
     * (not to be confused with the method getAirportCodes in the class city!)
     * @param input
     * @param mode
     * @return a vector of airport codes
     * @details Time complexity: O(1) (code mode) or O(n) (name mode) or O(k) + O(m) (city mode) or O(n) (coord mode), n being the size of the
     * airport hash table, k being the size of the input string and m being the size of the airport codes vector in the city.
     */
    vector<string> getAirportCode(string &input,string& mode);

    /**
     * Finds the best trip between source and destination, considering a filter
     * @param source
     * @param destination
     * @param optimalDist
     * @param filter
     * @return updated optimaldist and vector of vectors of [airportcode1, airlinecode1,airportcode2,airlinecode2]
     * @details Time complexity:
     */
    vector<vector<string>> getBestTrips(string source, string destination, int& optimalDist, const filter& filter);

    /**
     * Adds an airport to the graph
     * @param airport
     * @return true if successful, false if not
     */
    bool addAirport(const Airport& airport);
    /**
     * Adds a flight to source airport
     * @param source
     * @param flight
     * @return
     */
    bool addFlight(const string& source, const Flight& flight);
    /**
     * Adds an airline
     * @param airline
     */
    void addAirline(const Airline& airline);

    /**
     * @return the graph's airport hash table
     */
    unordered_map<int, Airport> getAirportTable() const;
    /**
     *
     * @return the graph's city hash table
     */
    unordered_map<int, City> getCityTable() const;
    /**
     * @return the graph's airline hash table
     */
    unordered_map<int, Airline> getAirlineTable() const;

    /**
     * Calculates the distance between two coordinates using the Haversine formula
     * @param lat1
     * @param lon1
     * @param lat2
     * @param lon2
     * @return distance between coord1 and coord2
     */
    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    /**
     * Calculates the number of different cities of the airports in vector v
     * @param v
     * @return the number of different cities
     */
    int calculateDifferentCities(vector<string> &v);
    /**
     * Calculates the number of different countries of the airports in vector v
     * @param v
     * @return the number of different countries
     */
    int calculateDifferentCountries(vector<string> &v);
    /**
     * Hash function to find an airport by code in the airports hash table
     * @param code
     * @return hash(code)
     * Time complexity: O(1)
     */
    int airportHash(const string& code);
    /**
     * Hash function to find a city by its name and country in the cities hash table
     * @param name
     * @param country
     * @return hash(name + country)
     * Time complexity: O(1)
     */
    int cityHash(const string& name, const string& country);
    /**
     * Hash function to find an airline by its code in the airlines hash table
     * @param code
     * @return hash(code)
     * Time complexity: O(1)
     */
    int airlineHash(const string& code);
    /**
     * Auxiliary dfs function to find the essential airports for flight communication
     * @param a
     * @param s
     * @param l
     * @param i
     * @param isRoot
     */
    void dfs_art(Airport& a, stack<Airport> &s, unordered_set<string> &l, int &i, bool isRoot);
    /**
     * @return a map in the format <cityName,<airlineCode,nrFlights (outgoing)>>
     */
    unordered_map<string, unordered_map<string, int>> getNumOutFlightsPerCityAirline();
    /**
     * @return a map in the format <cityName,<airlineCode,nrFlights (incoming)>>
     */
    unordered_map<string, unordered_map<string, int>> getNumInFlightsPerCityAirline();
    /**
     * @return a map in the format <airline,nrflights>
     */
    unordered_map<string, int> getNumFlightsPerAirline();
    /**
     * @return a map in the format <cityName, outgoingFlights>
     */
    unordered_map<string, int> getNumOutFlightsPerCity();
    /**
     * @return a map in the format <cityName, incomingFlights>
     */
    unordered_map<string, int> getNumInFlightsPerCity();
    /**
     * @param airportCode
     * @return the number of countries an airport flies to
     */
    int getNumCountriesFliesToByAirport(const string& airportCode);
    /**
     * @param cityName
     * @param cityCountry
     * @return the number of countries a city flies to
     */
    int getNumCountriesFliesToByCity(const string& cityName, string& cityCountry);
    /**
     * Finds the airports located k stops away from source
     * @param source
     * @param k
     * @return vector of airports located k stops away from source
     * @details Time complexity: O(n + m * n), n being the number of airports and m being the average number of flights per airport
     */
    vector<string> nodesAtDistanceBFS(Airport &source, int k);


};


#endif //PROJ2_AED_GRAPH_H
