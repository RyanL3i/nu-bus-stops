/*busstops.h*/

//
// A collection of bus stops in the Open Street Map.
// 
// Ryan Lei
// Northwestern University
// CS 211
// 

#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "busstop.h"

using namespace std;


/*
keep track of buildings in a map
*/

class BusStops
{
public:
    vector<BusStop> MapBusStops;

    /*
    constructor, takes in a file name and reads the bus stops from the file
    */
    BusStops(const std::string& filename);


    /*
    print, prints all the busStops by using the print function from the busstop class
    */
    void print() const;


   /*
    closest stops and distance, returns the closest north and soundbound stops and their distance away
    a pair of pairs, with the first pair being a busstop and its distance, and the second pair being a busstop and its distance.
    The first pair corresponds to North, second corresponding to South. 
    */
    
    pair<pair<BusStop, double>, pair<BusStop, double>> closestStopsAndDists(double lat, double lon) const;
};


