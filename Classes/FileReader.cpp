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
}

void FileReader::readAirports() {

}
