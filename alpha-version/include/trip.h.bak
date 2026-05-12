#include <iostream>
#include <string>
#include <vector>
using namespace std;
#pragma once
#include "bus.h"
#include "route.h"
class trip
{
private:
    long long trip_id;
    string trip_date;
    bus trip_bus;
    route trip_route;
    string trip_time;

public:
    void settrip_id(long long t_i);
    long long gettrip_id();
    
    void settrip_time(string t_t);
    string gettrip_time();


    void settrip_date(string t_d);
    string gettrip_date();

    void settrip_bus(bus& t_b);
    bus gettrip_bus();

    void settrip_route(route& t_r);
    route gettrip_route();

    trip(string t_d, bus& t_b, route& t_r,string t_t);
    ~trip();
};