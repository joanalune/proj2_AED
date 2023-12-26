#ifndef PROJ2_AED_FILEREADER_H
#define PROJ2_AED_FILEREADER_H

#include <unordered_map>
#include "Airport.h"
#include "Graph.h"

class FileReader{
private:
    Graph* graph;
public:
    FileReader(Graph* graph): graph(graph) {}

    void readAirlines();
    void readAirports();
    void readFlights();

};

#endif //PROJ2_AED_FILEREADER_H
