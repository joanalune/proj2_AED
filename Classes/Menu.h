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
    int runBestFlightsFiltersMenu(filter &filter);

    void printNrAirportsFlights();
    void printNrFlightsSpecifiedAirport();
    void printNrDestinationsAirport();

    void printTopAirports();
    void printGreatestNumberStops();
    void printEssentialAirports();
    void printBestFlights(vector<string> sources, vector<string> destinations, filter filter);

    void printNrFlightsCityAirline();
    void printNrDifferentCountries();

    void waitForInput() const;


    filter readFilterInput(int i);
};

#endif //PROJ2_AED_MENU_H
