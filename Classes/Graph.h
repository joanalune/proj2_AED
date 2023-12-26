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

    vector<string> airportCodeSet;      // vertex set
    int _index_;                        // auxiliary field
    stack<Airport> _stack_;           // auxiliary field
    list<list<string>> _list_sccs_;        // auxiliary field

    void dfsVisit(Airport *v, vector<string> & res) const;
    bool dfsIsDAG(Airport *v) const;
public:
    int getNumAirport() const;
    bool addAirport(const string &airportCode);
    bool removeVertex(const string &in);
    bool addEdge(const string &sourc, const string &dest, double w);
    bool removeEdge(const string &sourc, const string &dest);
    vector<string> getAirportCodeSet() const;
    vector<string> dfs() const;
    vector<string> dfs(const string & source) const;
    vector<string> bfs(const string &source) const;
    vector<string> topsort() const;
    bool isDAG() const;

    int airportHash(const string& airportCode);
};

/****************** Provided constructors and functions ********************/


int Graph::getNumAirport() const {
    return airportCodeSet.size();
}


vector<string> Graph::getAirportCodeSet() const {
    return airportCodeSet;
}


/*
 *  Adds a vertex with a given content or airport (in) to a graph (this).
 *  Returns true if successful, and false if a vertex with that content already exists.
 */

bool Graph::addAirport(const string &airportCode) {
    airportCodeSet.push_back(airportCode);
    return true;
}


/*
 * Adds an edge to a graph (this), given the contents of the source and
 * destination vertices and the edge weight (w).
 * Returns true if successful, and false if the source or destination vertex does not exist.
 */

bool Graph::addEdge(const string &sourc, const string &dest, const string &airline) {

    airportTable.->addEdge(v2,w);
    return true;
}

/*
 * Auxiliary function to add an outgoing edge to a vertex (this),
 * with a given destination vertex (d) and edge weight (w).
 */

void Airport::addEdge(Airport *d, double w) {
    flights.push_back(Flight(d, w));
}


/*
 * Removes an edge from a graph (this).
 * The edge is identified by the source (sourc) and destination (dest) contents.
 * Returns true if successful, and false if such edge does not exist.
 */

bool Graph::removeEdge(const string &sourc, const string &dest) {
    auto v1 = findVertex(sourc);
    auto v2 = findVertex(dest);
    if (v1 == NULL || v2 == NULL)
        return false;
    return v1->removeEdgeTo(v2);
}

/*
 * Auxiliary function to remove an outgoing edge (with a given destination (d))
 * from a vertex (this).
 * Returns true if successful, and false if such edge does not exist.
 */

bool Airport::removeEdgeTo(Airport *d) {
    for (auto it = adj.begin(); it != adj.end(); it++)
        if (it->dest  == d) {
            adj.erase(it);
            return true;
        }
    return false;
}

/*
 *  Removes a vertex with a given content (in) from a graph (this), and
 *  all outgoing and incoming edges.
 *  Returns true if successful, and false if such vertex does not exist.
 */

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


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) traversal in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order.
 * Follows the algorithm described in theoretical classes.
 */

vector<string> Graph::dfs() const {
    vector<string> res;
    for (auto v : vertexSet)
        v->visited = false;
    for (auto v : vertexSet)
        if (! v->visited)
            dfsVisit(v, res);
    return res;
}

/*
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Updates a parameter with the list of visited node contents.
 */

void Graph::dfsVisit(Airport *v, vector<string> & res) const {
    v->visited = true;
    res.push_back(v->airport);
    for (auto & e : v->adj) {
        auto w = e.dest;
        if ( ! w->visited)
            dfsVisit(w, res);
    }
}


/****************** DFS ********************/
/*
 * Performs a depth-first search (dfs) in a graph (this).
 * Returns a vector with the contents of the vertices by dfs order,
 * from the source node.
 */

vector<string> Graph::dfs(const string & source) const {
    vector<string> res;
    auto s = findVertex(source);
    if (s == nullptr)
        return res;

    for (auto v : vertexSet)
        v->visited = false;

    dfsVisit(s, res);
    return res;
}


/****************** BFS ********************/
/*
 * Performs a breadth-first search (bfs) in a graph (this), starting
 * from the vertex with the given source contents (source).
 * Returns a vector with the contents of the vertices by bfs order.
 */

vector<string> Graph::bfs(const string & source) const {
    vector<string> res;
    auto s = findVertex(source);
    if (s == NULL)
        return res;
    queue<Airport *> q;
    for (auto v : vertexSet)
        v->visited = false;
    q.push(s);
    s->visited = true;
    while (!q.empty()) {
        auto v = q.front();
        q.pop();
        res.push_back(v->airport);
        for (auto & e : v->adj) {
            auto w = e.dest;
            if ( ! w->visited ) {
                q.push(w);
                w->visited = true;
            }
        }
    }
    return res;
}


/****************** isDAG  ********************/
/*
 * Performs a depth-first search in a graph (this), to determine if the graph
 * is acyclic (acyclic directed graph or DAG).
 * During the search, a cycle is found if an edge connects to a vertex
 * that is being processed in the stack of recursive calls (see theoretical classes).
 * Returns true if the graph is acyclic, and false otherwise.
 */


bool Graph::isDAG() const {
    for (auto v : vertexSet) {
        v->visited = false;
        v->processing = false;
    }
    for (auto v : vertexSet)
        if (! v->visited)
            if ( ! dfsIsDAG(v) )
                return false;
    return true;
}

/**
 * Auxiliary function that visits a vertex (v) and its adjacent, recursively.
 * Returns false (not acyclic) if an edge to a vertex in the stack is found.
 */

bool Graph::dfsIsDAG(Airport *v) const {
    v->visited = true;
    v->processing = true;
    for (auto & e : v->adj) {
        auto w = e.dest;
        if (w->processing)
            return false;
        if (! w->visited)
            if (! dfsIsDAG(w))
                return false;
    }
    v->processing = false;
    return true;
}


/****************** toposort ********************/


vector<string> Graph::topsort() const {
    vector<string> res;

    //calculate in degree
    for (Airport* v : vertexSet) {
        v->setIndegree(0);
    }
    for (Airport* v : vertexSet) {
        for (Flight e : v->getAdj()) {
            e.dest->indegree++;
        }
    }

    queue<Airport*> toCheck; //holds all vertexes that "come next" (will change according to dynamic in degree)

    for (Airport* vertex : vertexSet) {

        if (vertex->getIndegree() == 0) {
            toCheck.push(vertex);
        }
    }

    while (!toCheck.empty()) {
        Airport* checkingV = toCheck.front();
        toCheck.pop();

        res.push_back(checkingV->getAirport());

        for (Flight adjEdge : checkingV->getAdj()) {
            adjEdge.getDest()->indegree--;

            if (adjEdge.getDest()->getIndegree() == 0) {
                toCheck.push(adjEdge.getDest());
            }
        }
    }

    if (res.size() != vertexSet.size()) {  //graph has a cycle
        res.clear();
    }


    return res;
};

#endif //PROJ2_AED_GRAPH_H
