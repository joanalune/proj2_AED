#ifndef PROJ2_AED_MENU_H
#define PROJ2_AED_MENU_H

#include "Graph.h"
#include "FileReader.h"

class Menu{
private:
    Graph graph;
public:
    Menu();

    void mainMenuView();
    void statisticsMenuView();
    void bestFlightsMenuView();
    void bestFlightsFiltersMenuView();

    int runMainMenu();
    int runStatisticsMenu();
    int runBestFlightsMenu();
    int runBestFlightsFiltersMenu();

    void printNrAirportsFlights();
    void printNrFlightsSpecifiedAirport();
    void printNrDestinationsAirport();

    void printTopAirports();
    void printGreatestNumberStops();
    void printEssentialAirports();
    void printBestFlights(vector<string> sources, vector<string> destinations, filter filter);


    void waitForInput() const;



};

#endif //PROJ2_AED_MENU_H
