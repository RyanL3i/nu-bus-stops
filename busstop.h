/*busstop.h*/

//
// A bus stop in the Open Street Map.
// 
// Ryan Lei
// Northwestern University
// CS 211
// 

#pragma once


#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"

using namespace std;


//
// BusStop
//
// Defines a bus stop with a stop ID, bus route, stop name, direction of travel, 
// and location of the stop, and the position
// in latitude and longitude
//

class BusStop
{
public:
    int StopID;
    int Route;
    string StopName;
    string Direction;
    string Location;
    double Lat;
    double Lon;


// constructor
BusStop(int stopID, int route, string stopName, string direction, string location, double lat, double lon);


/*
print

prints the busstop, id, route, stopname, etc..., passed via the csv file
*/
void print() const;


};
