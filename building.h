/*building.h*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#pragma once

#include <string>
#include <vector>

#include "node.h"
#include "nodes.h"
#include "busstops.h"

using namespace std;


//
// Building
//
// Defines a campus building with a name (e.g. "Mudd"), a street
// address (e.g. "2233 Tech Dr"), and the IDs of the nodes that
// define the position / outline of the building.
// 
// NOTE: the Name could be empty "", the HouseNumber could be
// empty, and the Street could be empty. Imperfect data.
//
class Building
{
public:
  long long ID;
  string Name;
  string StreetAddress;
  vector<long long> NodeIDs;

  //
  // constructor
  //
  Building(long long id, string name, string streetAddr);

  //
  // print
  // 
  // prints information about a building --- id, name, etc. -- to
  // the console. The function is passed the Nodes for searching 
  // purposes. Now prints information about which busstop to go to,
  // as well as when the buss may arrive via API data. 
  //
  void print(Nodes& nodes,  const BusStops &busStops);

  //
  // adds the given nodeid to the end of the vector.
  //
  void add(long long nodeid);

  /*
  pair, gets the center (lat, lon) of the building bsed on the ondes that form the perimeter
  */
  pair<double, double> getLocation(const Nodes& nodes);
};
