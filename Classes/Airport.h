#ifndef PROJ2_AED_AIRPORT_H
#define PROJ2_AED_AIRPORT_H

#include <vector>
#include "string"
#include "City.h"
#include "Flight.h"

using namespace std;

class Airport{
private:
    string code;
    string name;
    City city;
    double latitude;
    double longitude;

    vector<Flight> flights;  // list of outgoing edges
    bool visited;
    bool processing;

    void addEdge(Airport *dest, double latitude, double longitude);
    bool removeEdgeTo(Airport *dest);
public:
    Airport(string code, string name, City city, double latitude, double longitude);

    string getName() const;
    string getCode() const;
    City getCity() const;
    double getLatitude() const;
    double getLongitude() const;
    const vector<Flight> &getFlightsOut() const;

    void setCode(string code);
    void setName(string name);
    void setCity(City city);
    void setFlightsOut(const vector<Flight> &adj);

    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);

};

#endif //PROJ2_AED_AIRPORT_H
