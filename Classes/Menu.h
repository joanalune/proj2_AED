#ifndef PROJ2_AED_MENU_H
#define PROJ2_AED_MENU_H

#include "Graph.h"
#include "FileReader.h"

class Menu{
private:
    Graph graph;
public:
    /**
     * Default constructor
     */
    Menu();
    /**
     * Prints the main menu
     */
    void mainMenuView();
    /**
     * Prints the statistcs menu
     */
    void statisticsMenuView();
    /**
     * Prints the best flights menu
     */
    void bestFlightsMenuView();
    /**
     * Prints the filters menu
     */
    void bestFlightsFiltersMenuView();
    /**
     * Reads the option selected in the main menu
     */
    int runMainMenu();
    /**
     * Reads the option selected in the statistics menu
     */
    int runStatisticsMenu();
    /**
     * Reads the option selected in the best flights menu
     */
    int runBestFlightsMenu();
    /**
     * Reads the filter selected in the best flights menu(???)
     * @param filter
     * @return
     */
    int runBestFlightsFiltersMenu(filter &filter);
    /**
     * Prints the global number of airports and flights, calls the graph functions: getNrFlights() and getNrAirports()
     */
    void printNrAirportsFlights();
    /**
     * Prints the number of flights out of a specified airport, calls the graph functions: getOutDegree() and getNrDifferentAirlines()
     */
    void printNrFlightsSpecifiedAirport();
    /**
     * Prints the number of reachable destinations through a specified airport, calls the graph functions: calculateDifferentCities() and calculateDifferentCountries()
     */
    void printNrDestinationsAirport();
    /**
     * Prints the top X airports with the most flights (outgoing + incoming), calls the graph functions topAirports(), getInDegree() and getOutDegree()
     * @details Time Complexity: O(n), n being the number of airports the user wants printed + alguma cena provavlmente
     */
    void printTopAirports();
    /**
     * Prints the trips with the greatest number of stops, calls the graph function topAirports(), getInDegree() and getOutDegree()
     */
    void printGreatestNumberStops();
    /**
     * Prints the essential airports for the flight system
     */
    void printEssentialAirports();
    /**
     * ????????
     * @param sources
     * @param destinations
     * @param filter
     */
    void printBestFlights(vector<string> sources, vector<string> destinations, filter filter);
    /**
     *
     */
    void printNrFlightsCityAirline();
    /**
     *
     */
    void printNrDifferentCountries();
    /**
     * Waits for an user input in order to continue the program
     */
    void waitForInput() const;


    filter readFilterInput(int i);
};

#endif //PROJ2_AED_MENU_H
