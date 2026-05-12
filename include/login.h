#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include "datamigration.h"
#include "csvmanager.h"
#include "qrgenerator.h"

using namespace std;

class log : protected Request {
private:
    CSVManager csvManager;
    QRGenerator qrGenerator;

public:
    void login() {
        string email, password;
        cout << "Enter your email: ";
        cin >> email;
        cout << "Enter your password: ";
        cin >> password;

        // Check for admin login
        if (email == "admin" && password == "admin") {
            cout << "Admin login successful!" << endl;
            cout << "Welcome, Admin!" << endl;
            admin();
            return;
        }

        // Check for user login
        if (csvManager.authenticateUser(email, password)) {
            cout << "Login successful!" << endl;
            int userId = csvManager.getUserIdByEmail(email);
            user_menu(email);
        } else {
            cout << "Invalid email or password." << endl;
        }
    }

    void admin() {
        while (true) {
            cout << "\n=== ADMIN MENU ===" << endl;
            cout << "1. Manage Users" << endl;
            cout << "2. Manage Buses" << endl;
            cout << "3. Manage Routes" << endl;
            cout << "4. Manage Trips" << endl;
            cout << "5. Manage Reservations" << endl;
            cout << "6. Exit" << endl;
            cout << "Choose an option: ";
            
            int choice;
            cin >> choice;
            cin.ignore(); // Clear input buffer

            switch(choice) {
                case 1:
                    manage_users();
                    break;
                case 2:
                    manage_buses();
                    break;
                case 3:
                    manage_routes();
                    break;
                case 4:
                    manage_trips();
                    break;
                case 5:
                    manage_reservations();
                    break;
                case 6:
                    cout << "Exiting..." << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
            }
        }
    }

    void user_menu(const string& email) {
        user u = show_users_by_email(email);
        while (true) {
            cout << "\n=== USER MENU ===" << endl;
            cout << "1. Book a trip" << endl;
            cout << "2. Cancel a trip" << endl;
            cout << "3. View my bookings" << endl;
            cout << "4. Logout" << endl;
            cout << "Choose an option: ";
            
            int choice;
            cin >> choice;
            cin.ignore();

            switch(choice) {
                case 1: {
                    vector<vector<string>> trips = csvManager.getAllTrips();
                    display_trips(trips);
                    break;
                }
                case 2:
                    cancel_user_trip(u);
                    break;
                case 3:
                    view_user_bookings(u);
                    break;
                case 4:
                    cout << "Logging out..." << endl;
                    return;
                default:
                    cout << "Invalid choice." << endl;
            }
        }
    }

    void manage_users() {
        cout << "Adding a user..." << endl;
        cout << "Enter user name: ";
        string user_name;
        getline(cin, user_name);
        cout << "Enter user email: ";
        string user_email;
        getline(cin, user_email);
        cout << "Enter user password: ";
        string user_password;
        getline(cin, user_password);
        cout << "Enter user phone number: ";
        string user_phone;
        getline(cin, user_phone);
        
        user new_user(user_name, user_email, user_password, user_phone);
        save_user(new_user);
    }

    void manage_buses() {
        cout << "Adding a bus..." << endl;
        cout << "Enter bus driver name: ";
        string bus_driver;
        getline(cin, bus_driver);
        cout << "Enter bus capacity: ";
        int bus_capacity;
        cin >> bus_capacity;
        cin.ignore();
        
        route r = show_routes();
        bus new_bus(bus_driver, bus_capacity, r);
        save_bus(new_bus);
    }

    void manage_routes() {
        cout << "Adding a route..." << endl;
        cout << "Enter start location: ";
        string start_location;
        getline(cin, start_location);
        cout << "Enter end location: ";
        string end_location;
        getline(cin, end_location);
        cout << "Enter duration: ";
        string duration;
        getline(cin, duration);
        
        route new_route(duration, start_location, end_location);
        save_route(new_route);
    }

    void manage_trips() {
        cout << "Adding a trip..." << endl;
        cout << "Enter trip date (YYYY-MM-DD): ";
        string trip_date;
        getline(cin, trip_date);
        cout << "Enter trip time (HH:MM): ";
        string trip_time;
        getline(cin, trip_time);
        cout << "Enter price: ";
        int price;
        cin >> price;
        cin.ignore();
        
        bus b = show_buses();
        route r = b.getroute();
        trip new_trip(trip_date, b, r, trip_time);
        save_trip(new_trip, price);
    }

    void manage_reservations() {
        cout << "1. Book a trip" << endl;
        cout << "2. Cancel a trip" << endl;
        cout << "Choose an option: ";
        int reservation_choice;
        cin >> reservation_choice;
        cin.ignore();
        
        if(reservation_choice == 1){
            cout << "Booking a trip..." << endl;
            user u = show_users();
            cout << "Enter seat number: ";
            int seat_number;
            cin >> seat_number;
            book_trip(u, seat_number);
        }
        else if(reservation_choice == 2){
            cout << "Cancelling a trip..." << endl;
            user u = show_users();
            long long selected_trip = show_trips();
            cancel_trip(u, selected_trip);
        }
    }

    void display_trips(const vector<vector<string>>& trips) {
        if (trips.empty()) {
            cout << "No trips available." << endl;
            return;
        }

        for (size_t i = 0; i < trips.size() && i < 10; i++) {
            const auto& trip = trips[i];
            if (trip.size() >= 5) {
                cout << (i + 1) << ". " << trip[0] << " at " << trip[1] 
                     << " - EGP " << trip[2] << " (Seats: " << trip[3] << ")" << endl;
            }
        }
    }

    user show_users_by_email(const string& email) {
        ifstream file("data/users.csv");
        string line;
        getline(file, line); // Skip header
        
        while (getline(file, line)) {
            vector<string> fields;
            stringstream ss(line);
            string field;
            while (getline(ss, field, ',')) {
                fields.push_back(field);
            }
            if (fields.size() >= 4 && fields[3] == email) {
                file.close();
                return user(fields[0], fields[3], fields[2], fields[1]);
            }
        }
        file.close();
        return user("", "", "", "");
    }

    void cancel_user_trip(user& u) {
        ifstream file("data/reservations.csv");
        vector<string> reservations;
        string line;
        
        getline(file, line); // Skip header
        int i = 1;
        while (getline(file, line)) {
            reservations.push_back(line);
            if (line.find(to_string(u.getid_user())) != string::npos) {
                cout << i << ". " << line << endl;
            }
            i++;
        }
        file.close();

        cout << "Enter reservation number to cancel: ";
        int choice;
        cin >> choice;
        
        // Remove from file
        ofstream outFile("data/reservations.csv");
        outFile << "UserID,TripID,Seats,ReservationDate" << endl;
        i = 1;
        for (const auto& res : reservations) {
            if (i != choice) {
                outFile << res << endl;
            }
            i++;
        }
        outFile.close();
        cout << "Reservation cancelled." << endl;
    }

    void view_user_bookings(user& u) {
        ifstream file("data/reservations.csv");
        string line;
        getline(file, line); // Skip header
        
        cout << "Your Bookings:" << endl;
        int count = 0;
        while (getline(file, line)) {
            if (line.find(to_string(u.getid_user())) != string::npos) {
                cout << line << endl;
                count++;
            }
        }
        file.close();
        
        if (count == 0) {
            cout << "No bookings found." << endl;
        }
    }
};