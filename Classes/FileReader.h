#ifndef PROJ2_AED_FILEREADER_H
#define PROJ2_AED_FILEREADER_H

#include <unordered_map>
#include "Airport.h"
#include "Graph.h"

class FileReader{
private:
    Graph* graph;
public:
    /**
     * Constructor that receives the graph in use
     * @param graph
     */
    FileReader(Graph* graph): graph(graph) {}
    /**
     * Reads the airlines' codes, names, callsign and country and adds them to the graph's airlines hash table
     * @details Time complexity: O(n), n being the number of lines in airlines.csv file
     */
    void readAirlines();
    /**
     * Reads the airports' code, name, city, country, latitude and longitude and adds them to the graph's airports hash table
     * @details Time complexity: O(n), n being the number of lines in airports.csv file
     */
    void readAirports();
    /**
     * Reads the flights' destination and airline and adds them to each airport in the graph's airports hash table
     * @details Time complexity: O(n), n being the number of lines in flights.csv file
     */
    void readFlights();

};

#endif //PROJ2_AED_FILEREADER_H
