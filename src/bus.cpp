#include <iostream>
using namespace std;
#include "bus.h"
bus::bus(string b_d, int b_c, route& r) : bus_driver(b_d), bus_capacity(b_c), Route(r)
{
}
bus::~bus()
{
}
// setter and getter for driver name
void bus :: setbus_driver(string b_d)
{
    bus_driver = b_d;
}
string bus:: getbus_driver()
{
    return bus_driver;
}
//setter and getter for bus id
void bus:: setbus_id(long long b_i){
    bus_id=b_i;
}
long long bus ::getbus_id() {
    return bus_id;
}
//setter and getter for capacity
void bus::setbus_capacity(int b_c){
    bus_capacity=b_c;
}
int bus::getbus_capacity(){
    return bus_capacity;
}
//setter and getter for route
void bus::setRoute(route& r){
    Route=r;
}
route bus :: getroute(){
    return Route;
}
