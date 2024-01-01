#include <set>
#include <unordered_set>
#include <climits>
#include <sstream>
#include <cmath>
#include <iostream>
#include "Graph.h"

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wstring-plus-int"
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

bool Graph::addFlight(const string& source, const Flight& flight) {
    int sapHash = airportHash(source);
    int dapHash = airportHash(flight.getDestCode());
    int alHash = airlineHash(flight.getAirlineCode());
    if (airportTable.find(sapHash) == airportTable.end() || airportTable.find(dapHash) == airportTable.end()
        || airlineTable.find(alHash) == airlineTable.end()) return false;

    airportTable.at(sapHash).addFlight(flight);
    airportTable.at(dapHash).increaseInDegree();

    return true;
}

vector<string> Graph::dfs() {
    vector<string> res;

    for (auto& v : airportTable)
        v.second.setVisited(false);

    for (auto& v : airportTable)
        if (! v.second.isVisited())
            dfsVisit(v.second.getCode(), res);

    return res;
}

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

vector<string> Graph::dfs(const string & source) {
    vector<string> res;

    for (auto& v : airportTable)
        v.second.setVisited(false);

    dfsVisit(source, res);
    return res;
}


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

vector<string> Graph::farthestAirportsFrom(const string& source, int& stops) {
    vector<string> farthest;

    queue<string> q;
    for (auto& v : airportTable)
        v.second.setVisited(false);

    q.push(source);
    airportTable.at(airportHash(source)).setVisited(true);

    stops = 0;
    int qSize;

    while (!q.empty()) {
        qSize = q.size();
        farthest.clear();

        for (int i = 0; i < qSize; i++) {
            auto a = q.front();
            q.pop();
            farthest.push_back(a);

            for (auto &e: airportTable.at(airportHash(a)).getFlights()) {
                string dest = e.getDestCode();
                if (!airportTable.at(airportHash(dest)).isVisited()) {
                    q.push(dest);
                    airportTable.at(airportHash(dest)).setVisited(true);
                }
            }
        }
        stops++;
    }
    stops--;
    return farthest;
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

//--->Funciona<---//--voos de saida
unordered_map<string, unordered_map<string, int>> Graph::getNumOutFlightsPerCityAirline(){
    unordered_map<string, unordered_map<string, int>> flightsPerCityAirline;

    for(const auto& airport : airportTable){
        const string& cityName = airport.second.getCityName();
        const vector<Flight>& flights = airport.second.getFlights();

        for(const auto& flight : flights){
            string airlineCode = flight.getAirlineCode();

            flightsPerCityAirline[cityName][airlineCode]++;
        }
    }
    return flightsPerCityAirline;
}

unordered_map<string, unordered_map<string, int>> Graph::getNumInFlightsPerCityAirline() {
    unordered_map<string, unordered_map<string, int>> inFlightsPerCityAirline;

    for(const auto& airport : airportTable){
        const string& cityName = airport.second.getCityName();
        const vector<Flight>& flights = airport.second.getFlights();


        for(const auto& flight : flights){
            string airlineCode = flight.getAirlineCode();
            string destinationAirportCode = flight.getDestCode();

            auto destAirportIt = airportTable.find(airportHash(destinationAirportCode));
            if(destAirportIt != airportTable.end()){
                const string& destCityName = destAirportIt->second.getCityName();


                inFlightsPerCityAirline[destCityName][airlineCode]++;
            }
        }
    }
    return inFlightsPerCityAirline;
}


//---> Funciona -- retorna o mesmo numero q o size e q o in
unordered_map<string, int> Graph::getNumOutFlightsPerCity(){
    unordered_map<string, int> flightsPerCity;

    for (const auto& city : cityTable){
        int cityFlights = 0;
        const auto& airportCodes = city.second.getAirportCodes();

        for (const auto& code : airportCodes) {
            auto port = airportTable.find(airportHash(code));
            if (port != airportTable.end()) {

                cityFlights += port->second.getFlights().size();
                //cityFlights += port->second.getOutDegree();
            }
        }
        flightsPerCity[city.second.getName()] = cityFlights;
    }
    return flightsPerCity;
}

//---> Funciona -- mas retorna o mesmo numero q o size e out
unordered_map<string, int> Graph::getNumInFlightsPerCity(){
    unordered_map<string, int> flightsPerCity;

    for(const auto& city : cityTable){
        int cityFlights = 0;
        const auto& airportCodes = city.second.getAirportCodes();

        for(const auto& code : airportCodes){
            auto port = airportTable.find(airportHash(code));
            if (port != airportTable.end()) {

                // cityFlights += port->second.getFlights().size();
                cityFlights += port->second.getInDegree();
            }
        }
        flightsPerCity[city.second.getName()] = cityFlights;
    }
    return flightsPerCity;
}

//---> Funciona <---//
unordered_map<string, int> Graph::getNumFlightsPerAirline(){
    unordered_map<string, int> flightsPerAirline;

    for(const auto& airport : airportTable){
        const vector<Flight>& flights = airport.second.getFlights();

        for(const auto& flight : flights){
            string airlineCode = flight.getAirlineCode();

            if(flightsPerAirline.find(airlineCode) != flightsPerAirline.end()){
                flightsPerAirline[airlineCode]++;
            }else{
                flightsPerAirline[airlineCode] = 1;
            }
        }
    }
    return flightsPerAirline;
}


int Graph::getNumCountriesFliesToByAirport(const string& airportCode){
    unordered_set<string> countries;
    auto port = airportTable.find(airportHash(airportCode));

    if (port == airportTable.end()) {
        return -1;
    }
    const vector<Flight>& flights = port->second.getFlights();

    for (const auto& flight : flights){
        auto destPort = airportTable.find(airportHash(flight.getDestCode()));

        if (destPort != airportTable.end()){
            countries.insert(destPort->second.getCountryName());
        }
    }
    return countries.size();
}

int Graph::getNumCountriesFliesToByCity(const std::string &cityName, std::string &cityCountry){
    unordered_set<string> countries;

    for(const auto& city : cityTable){
        if(city.second.getName() == cityName && city.second.getCountry() == cityCountry){
            const vector<string>& airportCodes = city.second.getAirportCodes();
            for(const auto& code : airportCodes){
                auto port = airportTable.find(airportHash(code));

                if(port != airportTable.end()){
                    const vector<Flight>& flights = port->second.getFlights();

                    for(const auto& flight : flights){
                        auto destPort = airportTable.find(airportHash(flight.getDestCode()));
                        if(destPort != airportTable.end()){
                            countries.insert(destPort->second.getCountryName());
                        }
                    }
                }
            }
            break;
        }
    }
    return countries.size();
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

        double minDistance = std::numeric_limits<double>::max();

        for (const auto& a : airportTable) {
            double distance = calculateDistance(stod(lat), stod(longi), a.second.getLatitude(), a.second.getLongitude());

            if (distance < minDistance) {
                minDistance = distance;
                res.clear();
                res.push_back(a.second.code);
            } else if (distance == minDistance) {
                res.push_back(a.second.code);
            }
        }
    }

    return res;

}

vector<pair<string, string>> Graph::getMaximumTrip(int &diameter) { //returns a vector with pairs (source, destination) of graph diameter and places diameter in diameter
    vector<pair<string, string>> res;
    int stops = 0;
    int maxStops = 0;

    for (auto a : airportTable) {
        vector<string> farthest = farthestAirportsFrom(a.second.getCode(), stops);
        if (stops < maxStops) continue;
        if (stops > maxStops) res.clear();
        maxStops = stops;
        for (const string& dest : farthest) {
            res.emplace_back(a.second.getCode(), dest);
        }

    }
    diameter = maxStops;
    return res;
}

vector<vector<string>> Graph::getBestTrips(string source, string destination, int& optimalDist, const filter& filter) {
    vector<vector<string>> optimalPaths{};

    vector<string> optimalPath;

    queue<string> q;

    optimalDist = INT_MAX;

    for (auto &v: airportTable)
        v.second.setVisited(false);

    q.push(source);
    airportTable.at(airportHash(source)).setVisited(true);


    int stops = 0;
    int qSize;

    while (!q.empty() && stops < optimalDist) {
        qSize = q.size();

        for (int i = 0; i < qSize; i++) {
            auto a = q.front();
            q.pop();

            for (auto &e: airportTable.at(airportHash(a)).getFlights()) {

                //check airline blacklist/whitelist
                switch (filter.type) {
                    case 2:
                        //blacklist
                        if (filter.codes.find(e.getAirlineCode()) != filter.codes.end()) continue;
                        break;
                    case 1:
                        //whitelist
                        if (filter.codes.find(e.getAirlineCode()) == filter.codes.end()) continue;
                        break;
                }

                string dest = e.getDestCode();
                if (airportTable.at(airportHash(dest)).isVisited() && dest != destination) continue;
                airportTable.at(airportHash(dest)).setLastAirport(a);
                airportTable.at(airportHash(dest)).setLastAirline(e.getAirlineCode());

                if (dest == destination) {
                    optimalDist = stops;
                    optimalPath = vector<string>();
                    string pathFinder = dest;  // holds consecutively (backwards) each airport code that constitutes a path;

                    while (pathFinder != source) {
                        optimalPath.push_back(pathFinder);
                        optimalPath.push_back(airportTable.at(airportHash(pathFinder)).getLastAirline());
                        pathFinder = airportTable.at(airportHash(pathFinder)).getLastAirport();
                    }
                    optimalPath.push_back(pathFinder);  // add source;

                    optimalPaths.push_back(optimalPath);
                }
                if (!airportTable.at(airportHash(dest)).isVisited()) {
                    q.push(dest);
                    airportTable.at(airportHash(dest)).setVisited(true);
                }
            }
        }
        stops++;

    }

    return optimalPaths;
}

double Graph::calculateDistance(double lat1, double lon1, double lat2, double lon2) {
    const double radiusOfEarth = 6371.0;

    double dLat = (lat2 - lat1) * (M_PI / 180.0);
    double dLon = (lon2 - lon1) * (M_PI / 180.0);

    double a = sin(dLat / 2) * sin(dLat / 2) +
               cos(lat1 * (M_PI / 180.0)) * cos(lat2 * (M_PI / 180.0)) *
               sin(dLon / 2) * sin(dLon / 2);

    double c = 2 * atan2(sqrt(a), sqrt(1 - a));
    double distance = radiusOfEarth * c;

    return distance;
}

vector<string> Graph::nodesAtDistanceBFS(Airport &source, int k) {
    vector<string> res;
    queue<string> q;

    for (auto &a: airportTable) {
        a.second.setVisited(false);
    }

    int level = 0;

    q.push(source.getCode());

    while (!q.empty() && level <= k) {
        auto size = q.size();
        for (int i = 0; i < size; i++){
            auto v = q.front();
            airportTable.at(airportHash(q.front())).setVisited(true);

            for (auto f: airportTable.at(airportHash(q.front())).getFlights()) {
                if (!airportTable.at(airportHash(f.getDestCode())).isVisited()) {
                    airportTable.at(airportHash(f.getDestCode())).setVisited(true);
                    q.push(f.getDestCode());

                    res.push_back(f.getDestCode());

                }

            }
            q.pop();


        }
        level++;
    }

    return res;
}

int Graph::calculateDifferentCities(vector<string>& v){
    set<string> cities;
    for(auto s : v){
        cities.insert(airportTable.at(airportHash(s)).getCityName());
    }
    return cities.size();
}

int Graph::calculateDifferentCountries(vector<string>& v){
    set<string> countries;
    for(auto s : v){
        countries.insert(airportTable.at(airportHash(s)).getCountryName());
    }
    return countries.size();
}
