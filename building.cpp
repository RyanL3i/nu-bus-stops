/*building.cpp*/

//
// A building in the Open Street Map.
// 
// Prof. Joe Hummel
// Northwestern University
// CS 211
// 

#include <iostream>
#include "building.h"
#include <utility>
#include "busstops.h"
#include "busstop.h"
#include "curl_util.h"
#include "json.hpp"


using json = nlohmann::json;

using namespace std;


//
// constructor
//
Building::Building(long long id, string name, string streetAddr)
  : ID(id), Name(name), StreetAddress(streetAddr)
{
  //
  // the proper technique is to use member initialization list above,
  // in the same order as the data members are declared:
  //
  //this->ID = id;
  //this->Name = name;
  //this->StreetAddress = streetAddr;

  // vector is default initialized by its constructor
}

//
// print
// 
// prints information about a building --- id, name, etc. -- to
// the console. The function is passed the Nodes for searching 
// purposes. Now includes printing information about bus stops
// such as location, as well as bus live data via API data. 
//
void Building::print(Nodes& nodes, const BusStops &busStops)
{
  cout << this->Name << endl;
  cout << "Address: " << this->StreetAddress << endl;
  cout << "Building ID: " << this->ID << endl;
  cout << "# perimeter nodes: " << this->NodeIDs.size() << endl;
  cout << "Location: " << "(" << getLocation(nodes).first << ", " << getLocation(nodes).second << ")" << endl;

  auto closestStops = busStops.closestStopsAndDists(getLocation(nodes).first, getLocation(nodes).second);
  cout << "Closest southbound bus stop:" << endl;
  cout << "  " << closestStops.second.first.StopID << ": " 
  << closestStops.second.first.StopName 
  << ", bus #" << closestStops.second.first.Route 
  << ", " << closestStops.second.first.Location 
  <<", " << closestStops.second.second << " miles" << endl;

  CURL *curl = curl_easy_init();
  if (curl == nullptr)
  {
    cout << "**ERROR:" << endl;
    cout << "**ERROR: unable to initialize curl library" << endl;
    cout << "**ERROR:" << endl;
  }
  string url1 = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=f9ZYifve7euDPzMTcLAwwLLmd&rt=" + 
    to_string(closestStops.second.first.Route) + "&stpid=" + to_string(closestStops.second.first.StopID) + "&format=json";
  string response1;

  bool status1 = callWebServer(curl, url1, response1);

  if (status1 == false){
    cout << "  <<bus predictions unavailable, call failed>>" << endl;
  }

  else{
    auto jsondata = json::parse(response1);
    auto bus_response = jsondata["bustime-response"];
    auto predictions = bus_response["prd"];
    if (predictions.empty()){
      cout << "  <<no predictions available>>" << endl;
    }
    else{
      // looping through all of the predictions
      for (auto &M: predictions){
        try{
          cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>())
          << " on route " << stoi(M["rt"].get_ref<std::string&>())
          << " travelling " << M["rtdir"].get_ref<std::string&>()
          << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
        }
        catch(exception& e){
          cout << " error" << endl;
          cout << "malformed CTA response, prediction unavailable"
          << " (error: " << e.what() << ")" << endl;
        }
      }
    }
  }
  // printing north stuff
  cout << "Closest northbound bus stop:" << endl;
  cout << "  " << closestStops.first.first.StopID << ": " 
  << closestStops.first.first.StopName 
  << ", bus #" << closestStops.first.first.Route 
  << ", " << closestStops.first.first.Location 
  <<", " << closestStops.first.second << " miles" << endl;

  string url2 = "http://ctabustracker.com/bustime/api/v2/getpredictions?key=f9ZYifve7euDPzMTcLAwwLLmd&rt=" + 
    to_string(closestStops.first.first.Route) + "&stpid=" + to_string(closestStops.first.first.StopID) + "&format=json";
  string response2;
  bool status2 = callWebServer(curl, url2, response2);
  if (status2 == false){
    cout << "  <<bus predictions unavailable, call failed>>" << endl;
  }

  else{
    auto jsondata = json::parse(response2);
    auto bus_response = jsondata["bustime-response"];
    auto predictions = bus_response["prd"];
    if (predictions.empty()){
      cout << "  <<no predictions available>>" << endl;
    }
    else{
      // looping through all the predictions
      for (auto &M: predictions){
        try{
          cout << "  vehicle #" << stoi(M["vid"].get_ref<std::string&>())
          << " on route " << stoi(M["rt"].get_ref<std::string&>())
          << " travelling " << M["rtdir"].get_ref<std::string&>()
          << " to arrive in " << stoi(M["prdctdn"].get_ref<std::string&>()) << " mins" << endl;
        }
        catch(exception& e){
          cout << " error" << endl;
          cout << "malformed CTA response, prediction unavailable"
          << " (error: " << e.what() << ")" << endl;
        }
      }
    }
  }
}

//
// adds the given nodeid to the end of the vector.
//
void Building::add(long long nodeid)
{
  this->NodeIDs.push_back(nodeid);
}


/*
pair, gets the center (lat, lon) of the building based on the average of the nodes that form the perimeter
*/
pair<double, double> Building::getLocation(const Nodes& nodes)
{
  double avgLat = 0.0;
  double avgLon = 0.0;
  double totalLat = 0.0;
  double totalLon = 0.0;
  int count = 0;
  for (long long nodeid : this->NodeIDs)
  {
    double lat = 0.0;
    double lon = 0.0;
    bool entrance = false;

    bool found = nodes.find(nodeid, lat, lon, entrance);

    if (found) {
      totalLat += lat;
      totalLon += lon;
      count++;
    }
  }

  avgLat = totalLat / count;
  avgLon = totalLon / count;
  
  return make_pair(avgLat, avgLon);                                                                                                           
}