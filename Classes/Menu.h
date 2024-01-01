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
     * Prints the statistics menu
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
     * Asks the user which filter they want to use
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
     * Creates a non-directed version of the existing graph, prints the top X airports with the most flights (outgoing + incoming), calls the graph functions topAirports(), getInDegree() and getOutDegree()
     * @details Time Complexity: O(n) + O(i * log i) + O(j)*O(k), n being the number of airports the user wants printed, i being the size of the graph's airport table,
     * j being the size of the airport table and k being the size of the flights vector in each airport
     */
    void printTopAirports();
    /**
     * Prints the trips with the greatest number of stops, calls the graph function topAirports(), getInDegree() and getOutDegree()
     */
    void printGreatestNumberStops();
    /**
     * Prints the essential airports for the flight system. calls the graph function essential airports
     */
    void printEssentialAirports();
    /**
     * Prints the best flights from source to destination, depending on the filter
     * @param sources
     * @param destinations
     * @param filter
     */
    void printBestFlights(vector<string> sources, vector<string> destinations, filter filter);
    /**
     * Prints the number of flights by city or airline
     */
    void printNrFlightsCityAirline();
    /**
     * Prints the number of different countries a city/airport flies to
     */
    void printNrDifferentCountries();
    /**
     * Waits for an user input in order to continue the program
     */
    void waitForInput() const;

    /**
     * Reads user input
     * @param i
     * @return filter accordingly
     */
    filter readFilterInput(int i);
};

#endif //PROJ2_AED_MENU_H
