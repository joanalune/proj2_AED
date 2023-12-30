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
    void printBestFlights();


    void waitForInput() const;


    filter readFilterInput(int i);
};

#endif //PROJ2_AED_MENU_H
