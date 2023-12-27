#include <iostream>
#include "Menu.h"

using namespace std;

Menu::Menu() {
    graph = Graph();
    FileReader fileReader = FileReader(&graph);
    fileReader.readAirlines();
    fileReader.readAirports();
    fileReader.readFlights();
}

void Menu::waitForInput() const {
    cout << "Input any value to continue" << endl;
    string input;
    getline(cin >> input, input);
}

void Menu::mainMenuView() {
    cout << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << "  Air Travel Flight Management System   " << endl;
    cout    << "               Main Menu                " << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << endl;
    cout    << "What would you like to do?" << endl;
    cout    << "1. Consult network statistics"<< endl;
    cout    << "2. Search for best flight options" << endl;
    cout    << "3. Exit" << endl;
}

int Menu::runMainMenu() {
    while (true) {
        system("clear");
        mainMenuView();

        int option;
        cin >> option;

        switch (option) {
            case 1:
                runStatisticsMenu();
                break;
            case 2:
                runBestFlightsMenu();
                break;
            case 3:
                cout << "Thank you for using our Flight Management System ૮ ˶ᵔ ᵕ ᵔ˶ ა"<<endl;
                return 0;

            default:
                cout << "Invalid input" << endl;
        }
    }
}

void Menu::statisticsMenuView() {
    cout << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << "  Air Travel Flight Management System   " << endl;
    cout    << "          Network Statistics Menu       " << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << endl;
    cout    << "What would you like to know?" << endl;
    cout    << "1. Global number of airports/flights"<< endl;
    cout    << "2. Number of flights out of specified airport" << endl; //also print nr of airlines
    cout    << "3. Number of flights per city/airline" << endl;
    cout    << "4. Number of different countries a specified airport/city flies to" << endl;
    cout    << "5. Number of reachable destinations available for specified airport" << endl; //destinations being airports, cities or countries. needs to have options to select max nr of stops
    cout    << "6. Flight trips with the greatest number of stops" << endl;
    cout    << "7. Top X airports with the greatest flight capacity" << endl;
    cout    << "8. Essential airports for circulation capability" << endl; //articulation points
    cout    << "9. Exit" << endl;
}

int Menu::runStatisticsMenu() {
    while(true){
        system("clear");
        statisticsMenuView();
        int option;
        cin>>option;
        switch (option){
            case 1:
                printNrAirportsFlights();
                waitForInput();
                break;
            case 2:
                printNrFlightsSpecifiedAirport();
                waitForInput();
                break;
            case 3:
                //printNrFlightsPerCityAirline();
                waitForInput();
                break;
            case 4:
                //printNrDifferentCountries();
                waitForInput();
                break;
            case 5:
                //printNrDestinationsAirport();
                waitForInput();
                break;
            case 6:
                printGreatestNumberStops();
                waitForInput();
                break;
            case 7:
                printTopAirports();
                waitForInput();
                break;
            case 8:
                //printEssentialAirports();
                waitForInput();
                break;
            case 9:
                return 0;
            case 10:
                /*
                for (auto a : graph.getAirportTable()) {
                    cout << '\n' << a.second.getCode()  << "  " << a.second.getName() << "  " << a.second.getCountryName() << ',' << a.second.getCityName();
                }
                cout << '\n' << graph.getNumAirport();
                */
                /*
                for (auto a : graph.getCityTable()) {
                    cout << '\n' << a.second.getCountry() << ',' << a.second.getName() << "  " << a.second.getAirportCodes().size();
                }
                cout << '\n' << graph.getCityTable().size() << '\n';
                */
                /*
                for (auto a : graph.getAirlineTable()) {
                    cout << '\n' << a.second.getCode() << "  " << a.second.getCallSign() << "  " << a.second.getName() << "  " << a.second.getCountry();
                }
                cout << '\n' << graph.getAirlineTable().size() << '\n';
                */
            default:
                cout<<"Invalid input";
        }
    }
}
void Menu::bestFlightsMenuView() {
    cout    << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << "  Air Travel Flight Management System   " << endl;
    cout    << "            Best Flight Option          " << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << endl;
    cout    << "Insert your source and destination separated by a '-''" << endl;
    cout    << "For example: YCB-New York,United States or 35.016667,-1.450000-La Guardia"<< endl;
    cout    << "1. Exit" << endl;
}

int Menu::runBestFlightsMenu() {
    while (true) {
        system("clear");
        bestFlightsMenuView();

        int option;
        cin >> option;

        switch (option) {
            case 1:
                return 0;
            default:
                //printBestFlights(); //will ask for filters
                waitForInput();
                break;
        }
    }
}

void Menu::printNrAirportsFlights() {
    cout << "1. Global number of airports" << endl;
    cout << "2. Global number of flights" << endl;

    int option;
    cin >> option;

    switch (option) {
        case 1:
            cout << "The global number of airports is " << graph.getNumAirport() << endl;
            break;
        case 2:
            cout << "The global number of flights is " << graph.getNumFlights() << endl;
            break;
        default:
            cout << "Invalid input" << endl;
        }

}

void Menu::printNrFlightsSpecifiedAirport() {
    cout << "Enter airport code: " << endl;

    string airportCode;
    cin >> airportCode;

    auto findByCode = graph.airportHash(airportCode);

    if(graph.getAirportTable().find(findByCode) == graph.getAirportTable().end()){
        cout << "Airport not found!"<<endl;
    }

    else{
        cout << graph.getAirportTable().at(findByCode).getName() << " has " << graph.getAirportTable().at(findByCode).getOutDegree()<<
        " flights outgoing, from "<<graph.getAirportTable().at(findByCode).getNrDifferentAirlines()<<" different airlines."<<endl;
    }
}

void Menu::printTopAirports(){
    int in;
    cout << "Enter X:" << endl;
    cin >> in;
    graph.topAirports(in);
}

void Menu::printGreatestNumberStops() {
    int diameter;
    vector<pair<string, string>> diameterTrips = graph.getMaximumTrip(diameter);

    cout << "The trips with the greatest number of stops are:";
    for (auto pair : diameterTrips) {
        string s = graph.getAirportTable().at(graph.airportHash(pair.first)).getCode();
        string d = graph.getAirportTable().at(graph.airportHash(pair.second)).getCode();
        cout << '\n' << s << "  TO  " << d;
    }
    cout << "\nNumber of stops:  " << diameter << '\n';
}
