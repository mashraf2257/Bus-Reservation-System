#include <iostream>
using namespace std;
#pragma once
class route
{
private:
    int route_id;
    string start_location;
    string end_location;
    string duration;
public:
    void setroute_id(long long r_i);
    long long getroute_id() ;

    void setroute_duration(string r_d);
    string getroute_duration();

    void setroute_start(string r_s);
    string getroute_start();

    void setroute_end(string r_e);
    string getroute_end();
    route(string r_d,string r_s,string r_e);
    ~route();

};