#ifndef PROJ2_AED_GRAPH_H
#define PROJ2_AED_GRAPH_H

#include "string.h"
#include "Airport.h"
#include "city.h"

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
    int type;
    vector<string> codes;
};

class Graph {
    unordered_map<int, Airport> airportTable;
    unordered_map<int, City> cityTable;
    unordered_map<int, Airline> airlineTable;


    void dfsVisit(string apCode, vector<string> & res);
public:
    Graph();

    int getNumAirport() const;
    int getNumFlights() const;
    vector<pair<string, string>> getMaximumTrip(int &diameter);
    vector<string> farthestAirportsFrom(const string& source, int &stops);
    set<Airport> topAirports ();
    unordered_set<string> essentialAirports();
    vector<string> getAirportCode(string &input,string& mode);


    vector<vector<string>> getBestTrips(string source, string destination, int& optimalDist);


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

struct filter {
    int type;
    set<string> codes;
};

#endif //PROJ2_AED_GRAPH_H
