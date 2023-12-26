cmake_minimum_required(VERSION 3.27)
project(proj2_AED)

set(CMAKE_CXX_STANDARD 17)

add_executable(proj2_AED main.cpp
        Classes/City.cpp
        Classes/City.h
        Classes/Airline.h
        Classes/Airline.cpp
        Classes/Flight.h
        Classes/Flight.cpp
        Classes/Graph.cpp
        Classes/Graph.h
        Classes/Airport.cpp
        Classes/Airport.h)
