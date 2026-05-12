#include <iostream>
using namespace std;
#include "route.h"
route::route( string r_d, string r_s, string r_e) :  duration(r_d), start_location(r_s), end_location(r_e)
{
}
route::~route()
{
}
//setter and getter for id
void route::setroute_id(long long r_i)
{
    route_id=r_i;
}
long long route::getroute_id(){
    return route_id;
}
//setter and getter for duration
void route::setroute_duration(string r_d){
    duration=r_d;
}
string route::getroute_duration(){
    return duration;
}
//setter and getter for start location
void route::setroute_start(string r_s){
    start_location=r_s;
}
string route::getroute_start(){
    return start_location;
}
//setter and getter for end location
void route::setroute_end(string r_e){
    end_location=r_e;
}
string route::getroute_end(){
    return end_location;
}
