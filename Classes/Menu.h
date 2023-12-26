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

    int runMainMenu();
    int runStatisticsMenu();
    int runBestFlightsMenu();

    void printNrAirportsFlights();
    void printNrFlightsSpecifiedAirport();
    void printTopAirports();

    void waitForInput() const;
};

#endif //PROJ2_AED_MENU_H
