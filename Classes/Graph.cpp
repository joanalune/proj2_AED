#include <set>
#include <iostream>
#include <unordered_set>
#include <sstream>
#include "Graph.h"

Graph::Graph() {
    airportTable = {};
    airlineTable = {};
    cityTable = {};
}

int Graph::getNumAirport() const {
    return airportTable.size();
}

int Graph::getNumFlights() const {
    int res = 0;
    for(auto a: airportTable){
        res += a.second.getFlights().size();
    }
    return res;
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

int Graph::airportHash(const string &code) {
    hash<string> hash;
    return hash(code);
}

int Graph::cityHash(const string &name, const string &country) {
    hash<string> hash;
    return hash(name + country);
}

int Graph::airlineHash(const string &code) {
    hash<string> hash;
    return hash(code);
}

unordered_map<int, Airline> Graph::getAirlineTable() const {
    return airlineTable;
}

unordered_map<int, City> Graph::getCityTable() const {
    return cityTable;
}

set<Airport> Graph::topAirports() {
    int count = 0;

    set<Airport> orderedAirports;

    for(auto a : airportTable){
        orderedAirports.insert(a.second);
    }

    return orderedAirports;
}

unordered_set<string> Graph::essentialAirports() {
    unordered_set<string> res;
    int index=1;
    stack<Airport> s;
    for(auto a : airportTable){
        a.second.setVisited(false);
    }

    for(auto a : airportTable){
        if(!a.second.isVisited()) {
            dfs_art(a.second, s, res, index, true);
        }
    }

    return res;
}

void Graph::dfs_art(Airport& a, stack<Airport>& s, unordered_set<string>& l, int& i, bool isRoot){

    a.setNum(i);
    a.setLow(i);
    a.setProcessing(true);
    a.setVisited(true);
    i++;
    s.push(a);

    int children = 0;

    for (auto f : a.getFlights()){
        if(!airportTable.find(airportHash(f.getDestCode()))->second.isVisited()){
            children++;
            dfs_art(airportTable.find(airportHash(f.getDestCode()))->second,s,l,i,false);
            a.setLow(min(a.getLow(),airportTable.find(airportHash(f.getDestCode()))->second.getLow()));

            if((!isRoot && airportTable.find(airportHash(f.getDestCode()))->second.getLow() >= a.getNum()) || (isRoot && children > 1)){
                l.insert(a.getName());
            }
        }
        else if (airportTable.find(airportHash(f.getDestCode()))->second.isProcessing()){
            a.setLow(min(a.getLow(), airportTable.find(airportHash(f.getDestCode()))->second.getNum()));
        }
    }

    a.setProcessing(false);
    if(!isRoot){
        s.pop();
    }

}

vector<string> Graph::getAirportCode(string &input, string& mode) {
    vector<string> res;

    if(mode == "code"){
        auto found = airportTable.find(airportHash(input));
        if(found == airportTable.end()){
            return res;
        }
        else{
            res.push_back(input);
        }
    }

    if(mode == "name"){
        for(auto a : airportTable){
            if(a.second.name == input){
                res.push_back(a.second.code);
                break;
            }
        }
        return res;
    }

    if(mode == "city"){
        istringstream ss(input);
        string city, country;

        getline(ss, city, ',');
        getline(ss, country);

        auto found = cityTable.find(cityHash(city,country));
        if(found == cityTable.end()){
            return res;
        }
        else{
            for( auto a :found->second.getAirportCodes()){
                res.push_back(a);
            }
        }
    }

    if(mode == "coord"){
        istringstream ss(input);
        string lat, longi;

        getline(ss, lat, ',');
        getline(ss, longi);

        //ver quais sao aeroportos mais perto e fazer push back.

    }

}

