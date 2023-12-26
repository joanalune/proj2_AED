//
// Created by joana on 25-12-2023.
//


#include "Graph.h"

int Graph::getNumAirport() const {
    return airportTable.size();
}


unordered_map<int, Airport> Graph::getAirportTable() const {
    return airportTable;
}


/*
 *  Adds a vertex with a given content or airport (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addAirport(const Airport& airport) {
    int apHash = airportHash(airport.getCode());
    if (airportTable.find(apHash) != airportTable.end()) return false;

    airportTable.insert({apHash, airport});

    int cHash = cityHash(airport.getCityName(), airport.getCountryName());
    if (cityTable.find(cHash) == cityTable.end()) {
        cityTable.insert({cHash, City(airport.getCityName(), airport.getCountryName())});
    }
    cityTable.at(cHash).addAirportCode(airport.getCode());
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addFlight(const string& source, const Flight& flight) {
    int sapHash = airportHash(source);
    int dapHash = airportHash(flight.getDestCode());
    int alHash = airlineHash(flight.getAirlineCode());
    if (airportTable.find(sapHash) == airportTable.end() || airportTable.find(dapHash) == airportTable.end()
        || airlineTable.find(alHash) == airlineTable.end()) return false;

    airportTable.at(sapHash).addFlight(flight);
    return true;
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.


bool Graph::removeEdge(const string &sourc, const string &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}


 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.


bool Airport::removeEdgeTo(Airport *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}


 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.




bool Graph::removeVertex(const string &in) {
    for (auto it = vertexSet.begin(); it != vertexSet.end(); it++)
        if ((*it)->airport  == in) {
            auto v = *it;
            vertexSet.erase(it);
            for (auto u : vertexSet)
                u->removeEdgeTo(v);
            delete v;
            return true;
        }
    return false;
}
*/

/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */

vector<string> Graph::dfs() {
    vector<string> res;

    for (auto& v : airportTable)
        v.second.setVisited(false);

    for (auto& v : airportTable)
        if (! v.second.isVisited())
            dfsVisit(v.second.getCode(), res);

    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

void Graph::dfsVisit(string apCode, vector<string> & res) {
    int apHash = airportHash(apCode);
    airportTable.at(apHash).setVisited(true);

    res.push_back(apCode);

    for (auto & flight : airportTable.at(apHash).getFlights()) {
        string dest = flight.getDestCode();
        if ( ! airportTable.at(airportHash(dest)).isVisited())
            dfsVisit(dest, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */

vector<string> Graph::dfs(const string & source) {
    vector<string> res;

    for (auto& v : airportTable)
        v.second.setVisited(false);

    dfsVisit(source, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<string> Graph::bfs(const string & source) {
    vector<string> res;
    if (airportTable.find(airportHash(source)) == airportTable.end())
        return res;

    queue<string> q;
    for (auto& v : airportTable)
        v.second.setVisited(false);

    q.push(source);
    airportTable.at(airportHash(source)).setVisited(true);
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v);
        for (auto & e : airportTable.at(airportHash(v)).getFlights()) {
            string dest = e.getDestCode();
            if ( ! airportTable.at(airportHash(dest)).isVisited()) {
                q.push(dest);
                airportTable.at(airportHash(dest)).setVisited(true);
            }
        }
    }
    return res;
}

void Graph::addAirline(const Airline& airline) {
    airlineTable.insert({airlineHash(airline.getCode()), airline});
}
