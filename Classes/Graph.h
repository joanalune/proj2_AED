#ifndef PROJ2_AED_GRAPH_H
#define PROJ2_AED_GRAPH_H

#include "Airport.h"

class Graph{
        vector<Airport*> airports;      // vertex set

        void dfsVisit(Airport* airport, vector<Airport>& res) const;
    public:
        int getNumAirports() const;
        bool addAirport(const Airport& a);
        bool removeAirport(const Airport& a);
        bool addFlight(const Airport& source, const Airport& dest, const Airline& airline);
        bool removeFlight(const Airport& source, const Airport& dest);
        vector<Airport*> getVertexSet() const;
        vector<Airport> dfs() const;
        vector<Airport> dfs(const Airport& source) const;
        vector<Airport> bfs(const Airport& source) const;

};

#endif //PROJ2_AED_GRAPH_H
