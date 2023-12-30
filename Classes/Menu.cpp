#include <iostream>
#include <unordered_set>
#include <set>
#include <sstream>
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
                cout << "Thank you for using our Flight Management System (˶ᵔ ᵕ ᵔ˶)"<<endl;
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
    cout    << "5. Number of reachable destinations available for specified airport in a maximum number of X stops." << endl; //destinations being airports, cities or countries. needs to have options to select max nr of stops
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
                printNumFlightsPerCityAirline();
                //printNrFlightsCity();
                //printNrFlightsAirline();
                waitForInput();
                break;
            case 4:
                //printNrDifferentCountries();
                printNumCountriesFliesTo();
                waitForInput();
                break;
            case 5:
                printNrDestinationsAirport();
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
                printEssentialAirports();
                waitForInput();
                break;
            case 9:
                return 0;

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
    cout    << "Please insert your source location. Which format would you like to use?" << endl;
    cout    << "1. Airport Code" << endl;
    cout    << "2. Airport Name" << endl;
    cout    << "3. City and country" << endl;
    cout    << "4. Coordinates" << endl;
    cout    << "5. Exit" << endl;
}

int Menu::runBestFlightsMenu() {
    string mode, source, dest;
    vector<string> sourceAirports, destAirports;
    while (true) {
        system("clear");
        bestFlightsMenuView();

        int option1;
        cin >> option1;

        switch(option1){
            case 1:
                cout << "Please insert the source airport code:" << endl;
                cin >> source;
                mode = "code";
                break;

            case 2:
                cout << "Please insert the source airport name:" << endl;
                getline(std::cin >> std::ws, source);
                mode = "name";
                break;
            case 3:
                cout << "Please insert the source city and country in the format city,country:" << endl;
                getline(std::cin >> std::ws, source);
                mode = "city";
                break;
            case 4:
                cout << "Please insert the source coordinates in the format latitude,longitude:" << endl;
                cin >> source;
                mode = "coord";
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid input" << endl;
                return 0;
        }

        sourceAirports = graph.getAirportCode(source,mode);

        if(sourceAirports.empty()){
            cout << "Airports not found for source input!" << endl;
            waitForInput();
            return 0;
        }
        else{
            cout << "Airports to consider for source input: ";
            for(string code : sourceAirports){
                cout << code << " ";
            }
            cout << endl;
        }

        //destiny selection menu

        cout    << "Please insert your destiny location. Which format would you like to use?" << endl;
        cout    << "1. Airport Code" << endl;
        cout    << "2. Airport Name" << endl;
        cout    << "3. City and country" << endl;
        cout    << "4. Coordinates" << endl;
        cout    << "5. Exit" << endl;

        int option2;
        cin >> option2;

        switch(option2){
            case 1:
                cout << "Please insert the source airport code:" << endl;
                cin >> dest;
                mode = "code";
                break;

            case 2:
                cout << "Please insert the source airport name:" << endl;
                getline(std::cin >> std::ws, dest);
                mode = "name";
                break;
            case 3:
                cout << "Please insert the source city and country in the format city,country:" << endl;
                getline(std::cin >> std::ws, dest);
                mode = "city";
                break;
            case 4:
                cout << "Please insert the source coordinates in the format latitude,longitude:" << endl;
                cin >> dest;
                mode = "coord";
                break;
            case 5:
                return 0;
            default:
                cout << "Invalid input" << endl;
                return 0;
        }

        destAirports = graph.getAirportCode(dest,mode);

        if(destAirports.empty()){
            cout << "Airports not found for destination input!" << endl;
            waitForInput();
            return 0;
        }
        else{
            cout << "Airports to consider for destination input: ";
            for(string code : destAirports){
                cout << code << " ";
            }
            cout << endl;
        }

        runBestFlightsFiltersMenu();

    }
}

void Menu::bestFlightsFiltersMenuView() {
    cout    << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << "  Air Travel Flight Management System   " << endl;
    cout    << "     Best Flight Option - Filters       " << endl;
    cout    << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~" << endl;
    cout    << endl;
    cout    << "Which filters would you like to apply?" << endl;
    cout    << "1. No filters" << endl;
    cout    << "2. Use only certain airlines" << endl;
    cout    << "3. Avoid certain airlines" << endl;
    cout    << "4. Minimize airline changing" << endl;

}

int Menu::runBestFlightsFiltersMenu(){
    while (true) {
        system("clear");
        bestFlightsFiltersMenuView();

        int option;
        cin >> option;
        filter f;

        switch (option) {
            case 1:
                f = readFilterInput(0);
                break;
            case 2:
                cout << "Which airlines would you like to use? Please write them in the format airlinecode1,airlinecode2,..." << endl;
                f = readFilterInput(1);
                break;
            case 3:
                cout << "Which airlines would you like to avoid? Please write them in the format airlinecode1,airlinecode2,..." << endl;
                f = readFilterInput(2);
                break;
            case 4:
                f = readFilterInput(4);
                break;
            default:
                cout << "Invalid input" << endl;
                return 0;
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

void Menu::printNrDestinationsAirport() {
    vector<string> res;
    cout << "Enter airport code: " << endl;

    string airportCode;
    cin >> airportCode;

    cout << "Enter the maximum number of stops: " << endl;
    int in;
    cin >> in;

    if(graph.getAirportTable().find(graph.airportHash(airportCode)) == graph.getAirportTable().end() ){
        cout << "Airport not found!" << endl;
        return;
    }

    res = graph.nodesAtDistanceBFS(graph.getAirportTable().at(graph.airportHash(airportCode)),in);

    int differentCities = graph.calculateDifferentCities(res);
    int differentCountries = graph.calculateDifferentCountries(res);



    cout << airportCode << " can reach " << res.size() << " airports, " << differentCities <<" cities and " << differentCountries << " countries" " in a maximum number of " << in <<" stops." << endl;

}


void Menu::printNumFlightsPerCityAirline() {
    int option;
    cout << "1. Search flights by city/airline " << endl;
    cout << "2. Search flights by city" << endl;
    cout << "3. Search flights by airline" << endl;

    cin >> option;

    switch (option) {
        case 1: {
            unordered_map<string, unordered_map<string, int>> flightsPerCityAirline = graph.getNumFlightsPerCityAirline();
            cout << "Number of flights per City/Airline:" << endl;

            for (const auto& city : flightsPerCityAirline) {
                cout << "City: " << city.first << endl;

                for (const auto& airline : city.second) {
                    cout << "    Airline: " << airline.first << " - Flights: " << airline.second << endl;
                }
            }
            break;
        }
        case 2: {
            cout << "Number of flights per airline:" << endl;

            for (const auto& airport : graph.getAirportTable()) {
                cout << airport.second.getName() << " has " << airport.second.getOutDegree() <<
                     " flights outgoing, from " << airport.second.getNrDifferentAirlines() <<
                     " different airlines." << endl;
            }
            break;
        }
        case 3: {
            unordered_map<string, int> flightsPerCityAirline = graph.getNumFlightsPerAirline();
            cout << "Number of flights per airline:" << endl;

            for (const auto& pair : flightsPerCityAirline) {
                cout << pair.first << ": " << pair.second << " flights" << endl;
            }
            break;
        }
        default:
            cout << "Invalid choice." << endl;
            break;
    }
}

//--funcionam
/*
void Menu::printNumFlightsPerCityAirline() {
    unordered_map<string, unordered_map<string, int>> flightsPerCityAirline = graph.getNumFlightsPerCityAirline();

    cout << "Number of flights per City/Airline:" << endl;

    for (const auto& city : flightsPerCityAirline) {
        cout << "City: " << city.first << endl;

        for (const auto& airline : city.second) {
            cout << "    Airline: " << airline.first << " - Flights: " << airline.second << endl;
        }
    }
}
/*
void Menu::printNrFlightsCity() {
    for (const auto& airport : graph.getAirportTable()) {
        cout << airport.second.getName() << " has " << airport.second.getOutDegree() <<
             " flights outgoing, from " << airport.second.getNrDifferentAirlines() <<
             " different airlines." << endl;
    }
}
void Menu::printNrFlightsAirline() {
    unordered_map<string, int> flightsPerCityAirline = graph.getNumFlightsPerAirline();
    cout << "Number of flights per airline:" << endl;
    for (const auto& pair : flightsPerCityAirline) {
        cout << pair.first << ": " << pair.second << " flights" << endl;
    }
}
*/

void Menu::printNumCountriesFliesTo() {
    int option;
    cout << "1. Search by airport" << endl;
    cout << "2. Search by city" << endl;

    cin >> option;

    switch (option) {
        case 1: {
            cout << "Enter airport code: " << endl;
            string airportCode;
            cin >> airportCode;

            int numCountriesAirport = graph.getNumCountriesFliesToByAirport(airportCode);

            if (numCountriesAirport == -1) {
                cout << "Airport not found!" << endl;
            } else {
                cout << "The airport " << airportCode << " flies to " << numCountriesAirport << " different countries." << endl;
            }
            break;
        }
        case 2: {
            //Bug on cities with a space on the name
            cout << "Enter city name: " << endl;
            string cityName;
            cin >> cityName;

            cout << "Enter city country: " << endl;
            string cityCountry;
            cin >> cityCountry;

            int numCountriesCity = graph.getNumCountriesFliesToByCity(cityName, cityCountry);

            if (numCountriesCity == -1) {
                cout << "City not found or no flights from its airports!" << endl;
            } else {
                cout << "The city " << cityName << " airports fly to " << numCountriesCity << " different countries." << endl;
            }
            break;
        }
        default:
            cout << "Invalid input" << endl;
            break;
    }
}


void Menu::printTopAirports(){
    int in;
    cout << "Enter X:" << endl;
    cin >> in;

    int count =0;

    auto x = graph.topAirports();

    if(in >= graph.getAirportTable().size() || in <=0){
        cout << "Invalid input" << endl;
    }

    else{
        for(auto& a : x){
            if(count == in){break;}
            count++;
            cout << count << ". "<< a.getName() << ": "<< a.getInDegree() << " flights incoming and "<< a.getOutDegree() << " flights outgoing. " << a.getOutDegree() + a.getInDegree() << " flights total."<< endl;
        }
    }

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

void Menu::printEssentialAirports(){
    unordered_set<string> res;
    res = graph.essentialAirports();

    cout << "The essential airports "<< '(' << res.size() <<')'<<" are: " << endl;

    for(auto a : res){
        cout << a<< endl;
    }
}

void Menu::printBestFlights() {
    string source;
    string destination;

    cout << "\nsource?\n";
    cin >> source;
    cout << "\ndestination?\n";
    cin >> destination;

    int bestDist;
    vector<vector<string>> res = graph.getBestTrips(source, destination, bestDist);

    for (auto path : res) {
        for (int i = path.size() - 1; i >= 0; i--) {
            cout << path[i] << "  ";
        }
        cout << "\n";
    }

    cout << "best trip stops:" << bestDist << '\n';
}

filter Menu::readFilterInput(int i) {
    string codes;
    cin >> codes;

    std::getline(std::cin, codes);

    istringstream ss(codes);
    string code;

    set<string> code_set;

    while (getline(ss, code, ',')) {
        code_set.insert(code);
    }

    filter f = {i,code_set};

    return f ;

}



