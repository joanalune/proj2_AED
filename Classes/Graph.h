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
    int type;         // 0 - no filter; 1 - blacklist; 2 - whitelist; 3 - minimize airline changes. 1 and 2 are handled in getBestTrips (Graph class), 3 is handled in printBestFlights (Menu class)
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

    int getNumAirport() const;
    int getNumFlights() const;
    vector<pair<string, string>> getMaximumTrip(int &diameter);
    vector<string> farthestAirportsFrom(const string& source, int &stops);
    set<Airport> topAirports ();
    unordered_set<string> essentialAirports();
    vector<string> getAirportCode(string &input,string& mode);


    vector<vector<string>> getBestTrips(string source, string destination, int& optimalDist, const filter& filter);


    bool addAirport(const Airport& airport);
    bool removeVertex(const string &in);
    bool addFlight(const string& source, const Flight& flight);
    bool removeEdge(const string &sourc, const string &dest);
    void addAirline(const Airline& airline);


    unordered_map<int, Airport> getAirportTable() const;
    unordered_map<int, City> getCityTable() const;
    unordered_map<int, Airline> getAirlineTable() const;
    vector<string> dfs();
    vector<string> dfs(const string & source);
    vector<string> bfs(const string &source);
    void dfsVisit(string apCode, vector<string> & res);


    double calculateDistance(double lat1, double lon1, double lat2, double lon2);
    int calculateDifferentCities(vector<string> &v);
    int calculateDifferentCountries(vector<string> &v);

    int airportHash(const string& code);
    int cityHash(const string& name, const string& country);
    int airlineHash(const string& code);

    void dfs_art(Airport& a, stack<Airport> &s, unordered_set<string> &l, int &i, bool isRoot);

    unordered_map<string, unordered_map<string, int>> getNumOutFlightsPerCityAirline();
    unordered_map<string, unordered_map<string, int>> getNumInFlightsPerCityAirline();
    unordered_map<string, int> getNumFlightsPerAirline();
    unordered_map<string, int> getNumOutFlightsPerCity();
    unordered_map<string, int> getNumInFlightsPerCity();


    int getNumCountriesFliesToByAirport(const string& airportCode);
    int getNumCountriesFliesToByCity(const string& cityName, string& cityCountry);
    vector<string> nodesAtDistanceBFS(Airport &source, int k);


};


#endif //PROJ2_AED_GRAPH_H
