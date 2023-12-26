#ifndef PROJ2_AED_GRAPH_H
#define PROJ2_AED_GRAPH_H

#include "string.h"
#include "Airport.h"

#include <cstddef>
#include <vector>
#include <queue>
#include <stack>
#include <list>
#include <unordered_map>

using namespace std;


class Graph {
    unordered_map<int, Airport> airportTable;
    unordered_map<int, City> cityTable;
    unordered_map<int, Airline> airlineTable;


    void dfsVisit(string apCode, vector<string> & res);
public:
    Graph();

    int getNumAirport() const;
    int getNumFlights() const;
    void topAirports (int x);

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


    int airportHash(const string& code);
    int cityHash(const string& name, const string& country);
    int airlineHash(const string& code);
};



#endif //PROJ2_AED_GRAPH_H
