/*busstops.cpp*/

//
// A collection of bus stops in the Open Street Map.
// 
// Ryan Lei
// Northwestern University
// CS 211
// 
#include "busstops.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include "dist.h"
#include <algorithm>
#include <vector>
#include <limits>


/*
constructor, takes in file and reads it, mapping to array of sorted bus stops by STOP ID
*/
BusStops::BusStops(const std::string& filename) 
{
    ifstream input(filename);

    if (!input.is_open()) 
    {
        cerr << "Error opening file: " << filename << endl;
        exit(EXIT_FAILURE);
    }

    string line;
    while (getline(input, line)) 
    {
        stringstream parser(line);
        int stopID, busRoute;
        string stopName, direction, location;
        double latitude, longitude;

        // Parsing
        parser >> stopID;
        parser.ignore(); 
        parser >> busRoute;
        parser.ignore(); 
        getline(parser, stopName, ',');
        getline(parser, direction, ',');
        getline(parser, location, ',');
        parser >> latitude;
        parser.ignore(); 
        parser >> longitude;


        MapBusStops.emplace_back(stopID, busRoute, stopName, direction, location, latitude, longitude);
    }

    input.close();

    // sort the current map by ascending StopID order
    sort(MapBusStops.begin(), MapBusStops.end(),
              [](const BusStop& a, const BusStop& b) {
                  return a.StopID < b.StopID;
              });
}

/*
print, prints all the busStops by using the print function from the busstop class
*/

void BusStops::print() const 
{
    for (const auto& busStop : MapBusStops) 
    {
        busStop.print();
    }
}



/*
helper functions that check if the bus stop is north or southbound
*/

bool isNorthBound(const BusStop& busStop)
{
    return busStop.Direction == "Northbound";
}

bool isSouthBound(const BusStop& busStop)
{
    return busStop.Direction == "Southbound";
}

 /*
closest stops, returns the closest north and soundbound stops
*/



/*
closest stops and distance, returns the closest north and soundbound stops and their distance away
a pair of pairs, with the first pair being a busstop and its distance, and the second pair being a busstop and its distance.
The first pair corresponds to North, second corresponding to South. 
*/
pair<pair<BusStop, double>, pair<BusStop, double>> BusStops::closestStopsAndDists(double lat, double lon) const
{
    // Initialize closest stops and distances
    pair<BusStop, double> closestStopNorth(BusStop(0, 0, "", "", "", 0, 0), numeric_limits<double>::max());
    pair<BusStop, double> closestStopSouth(BusStop(0, 0, "", "", "", 0, 0), numeric_limits<double>::max());

    for (const auto& busStop : MapBusStops)
    {
        double currDist = distBetween2Points(lat, lon, busStop.Lat, busStop.Lon);

        // Check for Northbound stops
        if (isNorthBound(busStop) && currDist < closestStopNorth.second)
        {
            closestStopNorth = make_pair(busStop, currDist);
        }

        // Check for Southbound stops
        if (isSouthBound(busStop) && currDist < closestStopSouth.second)
        {
            closestStopSouth = make_pair(busStop, currDist);
        }
    }

    return make_pair(closestStopNorth, closestStopSouth);
}









