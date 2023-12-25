#include <fstream>
#include <sstream>
#include "FileReader.h"

void FileReader::readAirlines() {
    string code, name, callSign, country;

    ifstream file("../dataset/airlines.csv");

    string line;

    getline(file, line); // Skip header line

    while (getline(file, line)){
        if (line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        stringstream linestream(line);
        getline(linestream, code, ',');
        getline(linestream, name, ',');
        getline(linestream, callSign, ',');
        getline(linestream, country);

        Airline* airline = new Airline(code, name, callSign, country);

        airlines.insert({}); //insert in hash table

    }
    file.close();
}

void FileReader::readAirports() {
    string code, name, city, country, latitude, longitude;

    ifstream file("../dataset/airports.csv");

    string line;

    getline(file, line); // Skip header line

    while (getline(file, line)){
        if (line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        stringstream linestream(line);
        getline(linestream, code, ',');
        getline(linestream, name, ',');
        getline(linestream, city, ',');
        getline(linestream, country, ',');
        getline(linestream, latitude, ',');
        getline(linestream, longitude);

        City citat = City(city, country);

        //Airport *airport = new Airport(code, name, citat, latitude, longitude);

        airports.insert({}); //insert in hash table

    }
    file.close();
}

void FileReader::readFlights() {
    string source, target, airline;

    ifstream file("../dataset/flights.csv");

    string line;

    getline(file, line); // Skip header line

    while (getline(file, line)){
        if (line[line.size() - 1] == '\r') {
            line.resize(line.size() - 1);
        }
        stringstream linestream(line);
        getline(linestream, source, ',');
        getline(linestream, target, ',');
        getline(linestream, airline);

        //addvertex(source,target,airline)

    }
    file.close();
}
