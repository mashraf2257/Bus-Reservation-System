#pragma once
#include <iostream>
#include <vector>
#include "csvmanager.h"
#include "database.h"
#include "user.h"
#include "bus.h"
#include "route.h"
#include "trip.h"

using namespace std;

class Request {
private:
    CSVManager csvManager;

public:
    Request() = default;

    // Save user to CSV
    void save_user(user& u) {
        bool success = csvManager.saveUser(u.getname_user(), u.getemail_user(), 
                                          u.getpassword_user(), u.getphonenumber_user());
        if (success) {
            int userId = csvManager.getUserIdByEmail(u.getemail_user());
            u.setid_user(userId);
            cout << "User inserted successfully." << endl;
        }
    }

    // Save route to CSV
    void save_route(route& r) {
        bool success = csvManager.saveRoute(r.getroute_start(), r.getroute_end(), r.getroute_duration());
        if (success) {
            int routeId = csvManager.getRouteIdByName(r.getroute_start(), r.getroute_end());
            r.setroute_id(routeId);
        }
    }

    // Save bus to CSV
    void save_bus(bus& b) {
        int routeId = b.getroute().getroute_id();
        bool success = csvManager.saveBus(b.getbus_driver(), b.getbus_capacity(), routeId);
        if (success) {
            int busId = csvManager.getBusIdByDriver(b.getbus_driver());
            b.setbus_id(busId);
        }
    }

    // Save trip to CSV
    void save_trip(trip& t, int price) {
        int busId = t.gettrip_bus().getbus_id();
        int routeId = t.gettrip_route().getroute_id();
        bool success = csvManager.saveTrip(t.gettrip_date(), t.gettrip_time(), price, busId, routeId);
        if (success) {
            int tripId = csvManager.getTripIdByDetails(t.gettrip_date(), busId);
            t.settrip_id(tripId);
        }
    }

    // Show and select users
    user show_users() {
        ifstream file("data/users.csv");
        vector<user> users;
        int i = 1;
        string line;
        
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            if (fields.size() >= 4) {
                cout << i << ". " << fields[0] << " " << fields[3] << endl;
                users.push_back(user(fields[0], fields[3], fields[2], fields[1]));
                i++;
            }
        }
        file.close();

        cout << "Enter a number: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= users.size()) {
            return users[choice - 1];
        } else {
            cout << "Invalid choice." << endl;
            return show_users();
        }
    }

    // Show and select buses
    bus show_buses() {
        ifstream file("data/buses.csv");
        vector<bus> buses;
        int i = 1;
        string line;
        
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            if (fields.size() >= 3) {
                cout << i << ". " << fields[0] << " (Capacity: " << fields[1] << ")" << endl;
                route r("dummy", "start", "end");
                r.setroute_id(stoi(fields[2]));
                buses.push_back(bus(fields[0], stoi(fields[1]), r));
                i++;
            }
        }
        file.close();

        cout << "Enter a number: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= buses.size()) {
            return buses[choice - 1];
        } else {
            cout << "Invalid choice." << endl;
            return show_buses();
        }
    }

    // Show and select routes
    route show_routes() {
        ifstream file("data/routes.csv");
        vector<route> routes;
        int i = 1;
        string line;
        
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            if (fields.size() >= 3) {
                cout << i << ". " << fields[0] << " -> " << fields[1] << " (" << fields[2] << ")" << endl;
                routes.push_back(route(fields[2], fields[0], fields[1]));
                i++;
            }
        }
        file.close();

        cout << "Enter a number: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= routes.size()) {
            return routes[choice - 1];
        } else {
            cout << "Invalid choice." << endl;
            return show_routes();
        }
    }

    // Show and select trips
    long long show_trips() {
        vector<vector<string>> trips = csvManager.getAllTrips();
        int i = 1;
        vector<long long> tripIds;
        
        for (const auto& trip : trips) {
            if (trip.size() >= 5) {
                cout << i << ". " << trip[0] << " at " << trip[1] << " - EGP " << trip[2] << endl;
                tripIds.push_back(i + 4000000);
                i++;
            }
        }

        cout << "Enter a number: ";
        int choice;
        cin >> choice;
        if (choice >= 1 && choice <= tripIds.size()) {
            return tripIds[choice - 1];
        } else {
            cout << "Invalid choice." << endl;
            return show_trips();
        }
    }

    // Book a trip
    void book_trip(user& u, int selected_seat) {
        long long tripId = show_trips();
        long long userId = u.getid_user();
        
        csvManager.saveReservation(userId, tripId, to_string(selected_seat));
        cout << "Trip booked successfully." << endl;
    }

    // Cancel a trip
    void cancel_trip(user& u, long long selectedTrip) {
        ifstream file("data/reservations.csv");
        vector<string> lines;
        string line;
        bool found = false;
        
        while (getline(file, line)) {
            lines.push_back(line);
        }
        file.close();

        ofstream outFile("data/reservations.csv");
        for (const auto& l : lines) {
            if (l.find(to_string(u.getid_user())) == string::npos) {
                outFile << l << endl;
            } else {
                found = true;
            }
        }
        outFile.close();

        if (found) {
            cout << "Trip canceled successfully." << endl;
        } else {
            cout << "Trip not found." << endl;
        }
    }
};
