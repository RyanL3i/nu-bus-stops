/*busstop.cpp*/

//
// A bus stop in the Open Street Map.
// 
// Ryan Lei
// Northwestern University
// CS 211
// 

#include <iostream>

#include "busstop.h"

#include <utility>

# include "json.hpp"

using json = nlohmann::json;

using namespace std;

// constructor
BusStop::BusStop(int stopID, int route, string stopName, string direction, string location, double lat, double lon)
: StopID(stopID), Route(route), StopName(stopName), Direction(direction), Location(location), Lat(lat), Lon(lon)
{
    //
    // the proper technique is to use member initialization list above,
    // in the same order as the data members are declared:
    //this->StopID = stopID;
    //this->Route = route;
    //this->StopName = stopName;
    //this->Direction = direction;
    //this->Location = location;
    //this->Lat = lat;
    //this->Lon = lon;
    // vector is default initialized by its constructor
}


/*
print

prints the busstop, id, route, stopname, etc..., passed via the csv file
*/
void BusStop::print() const
{
    cout << this->StopID  << ": "
    << "bus " << this->Route << ", "
    << this->StopName << ", "
    << this->Direction << ", "
    << this->Location << ", "
    << "location (" << this->Lat << ", "
    << this->Lon << ")" << endl;
}



