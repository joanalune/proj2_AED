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
    int inDegree;

    void addFlight(Flight flight);
    bool removeEdgeTo(Airport *d);
public:


    Airport(string airportCode, string name, string cityName, string countryName, double latitude, double longitude);
    string getName() const;
    string getCode() const;
    string getCityName() const;
    string getCountryName() const;
    double getLatitude() const;
    double getLongitude() const;

    void setCode(const string &code);
    void setName(const string &name);
    void setCity(const City &city);

    bool isVisited() const;
    void setVisited(bool v);
    bool isProcessing() const;
    void setProcessing(bool p);
    const vector<Flight> &getFlights() const;

    int getOutDegree() const;
    void setInDegree(int inDegree);


    int getNum() const;
    int getLow() const;
    void setNum(int num);
    void setLow(int low);

    int getNrDifferentAirlines() const;

    bool operator<(Airport b) const;

    friend class Graph;



};


#endif //PROJ2_AED_AIRPORT_H
