#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <map>

using namespace std;

class CSVManager {
private:
    string dataDir = "data/";

    // Ensure data directory exists
    void ensureDataDir() {
        // Create data folder if it doesn't exist
        system("if not exist data mkdir data");
    }

    // Split CSV line into fields
    vector<string> parseCSVLine(const string& line) {
        vector<string> result;
        string field;
        bool insideQuotes = false;

        for (size_t i = 0; i < line.length(); i++) {
            char c = line[i];

            if (c == '"') {
                insideQuotes = !insideQuotes;
            } else if (c == ',' && !insideQuotes) {
                result.push_back(field);
                field.clear();
            } else {
                field += c;
            }
        }
        result.push_back(field);
        return result;
    }

    // Escape CSV field
    string escapeCSVField(const string& field) {
        if (field.find(',') != string::npos || field.find('"') != string::npos) {
            string escaped = "\"";
            for (char c : field) {
                if (c == '"') escaped += "\"\"";
                else escaped += c;
            }
            escaped += "\"";
            return escaped;
        }
        return field;
    }

public:
    CSVManager() {
        ensureDataDir();
    }

    // ==================== USER CSV OPERATIONS ====================
    bool userExists(const string& email) {
        ifstream file(dataDir + "users.csv");
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 3 && fields[3] == email) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool saveUser(const string& name, const string& email, const string& password, const string& phone) {
        if (userExists(email)) {
            cout << "Email already exists." << endl;
            return false;
        }

        ofstream file(dataDir + "users.csv", ios::app);
        if (!file.is_open()) {
            cerr << "Cannot open users.csv" << endl;
            return false;
        }

        file << escapeCSVField(name) << ","
             << escapeCSVField(phone) << ","
             << escapeCSVField(password) << ","
             << escapeCSVField(email) << endl;

        cout << "User saved successfully." << endl;
        file.close();
        return true;
    }

    int getUserIdByEmail(const string& email) {
        ifstream file(dataDir + "users.csv");
        if (!file.is_open()) return -1;

        string line;
        int userId = 1000000;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 3 && fields[3] == email) {
                file.close();
                return userId;
            }
            userId++;
        }
        file.close();
        return -1;
    }

    bool authenticateUser(const string& email, const string& password) {
        ifstream file(dataDir + "users.csv");
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 3 && fields[3] == email && fields[2] == password) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    // ==================== ROUTE CSV OPERATIONS ====================
    bool routeExists(const string& start, const string& end) {
        ifstream file(dataDir + "routes.csv");
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 2 && fields[0] == start && fields[1] == end) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool saveRoute(const string& start, const string& end, const string& duration) {
        if (routeExists(start, end)) {
            cout << "Route already exists." << endl;
            return false;
        }

        ofstream file(dataDir + "routes.csv", ios::app);
        if (!file.is_open()) {
            // Create header if file doesn't exist
            ofstream newFile(dataDir + "routes.csv");
            newFile << "Start,End,Duration" << endl;
            newFile.close();
            file.open(dataDir + "routes.csv", ios::app);
        }

        file << escapeCSVField(start) << ","
             << escapeCSVField(end) << ","
             << escapeCSVField(duration) << endl;

        cout << "Route saved." << endl;
        file.close();
        return true;
    }

    int getRouteIdByName(const string& start, const string& end) {
        ifstream file(dataDir + "routes.csv");
        if (!file.is_open()) return -1;

        string line;
        int routeId = 3000000;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 2 && fields[0] == start && fields[1] == end) {
                file.close();
                return routeId;
            }
            routeId++;
        }
        file.close();
        return -1;
    }

    // ==================== BUS CSV OPERATIONS ====================
    bool busExists(const string& driver) {
        ifstream file(dataDir + "buses.csv");
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 0 && fields[0] == driver) {
                file.close();
                return true;
            }
        }
        file.close();
        return false;
    }

    bool saveBus(const string& driver, int capacity, int routeId) {
        if (busExists(driver)) {
            cout << "Bus already exists." << endl;
            return false;
        }

        ofstream file(dataDir + "buses.csv", ios::app);
        if (!file.is_open()) {
            // Create header if file doesn't exist
            ofstream newFile(dataDir + "buses.csv");
            newFile << "Driver,Capacity,RouteID" << endl;
            newFile.close();
            file.open(dataDir + "buses.csv", ios::app);
        }

        file << escapeCSVField(driver) << ","
             << capacity << ","
             << routeId << endl;

        cout << "Bus inserted successfully." << endl;
        file.close();
        return true;
    }

    int getBusIdByDriver(const string& driver) {
        ifstream file(dataDir + "buses.csv");
        if (!file.is_open()) return -1;

        string line;
        int busId = 2000000;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 0 && fields[0] == driver) {
                file.close();
                return busId;
            }
            busId++;
        }
        file.close();
        return -1;
    }

    // ==================== TRIP CSV OPERATIONS ====================
    bool tripExists(const string& date, int busId, int routeId) {
        ifstream file(dataDir + "Trips.csv");
        if (!file.is_open()) return false;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 4 && fields[0] != "" && fields[2] != "") {
                // Just check if similar trip exists
                return false; // Allow multiple trips for now
            }
        }
        file.close();
        return false;
    }

    bool saveTrip(const string& date, const string& time, int price, int busId, int routeId) {
        ofstream file(dataDir + "Trips.csv", ios::app);
        if (!file.is_open()) {
            // Create header if file doesn't exist
            ofstream newFile(dataDir + "Trips.csv");
            newFile << "Date,Time,Price,BusID,RouteID" << endl;
            newFile.close();
            file.open(dataDir + "Trips.csv", ios::app);
        }

        file << escapeCSVField(date) << ","
             << escapeCSVField(time) << ","
             << price << ","
             << busId << ","
             << routeId << endl;

        cout << "Trip saved." << endl;
        file.close();
        return true;
    }

    int getTripIdByDetails(const string& date, int busId) {
        ifstream file(dataDir + "Trips.csv");
        if (!file.is_open()) return -1;

        string line;
        int tripId = 4000000;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (fields.size() > 3 && fields[0] == date) {
                file.close();
                return tripId;
            }
            tripId++;
        }
        file.close();
        return -1;
    }

    vector<vector<string>> getAllTrips() {
        vector<vector<string>> trips;
        ifstream file(dataDir + "Trips.csv");
        if (!file.is_open()) return trips;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            if (!line.empty()) {
                trips.push_back(parseCSVLine(line));
            }
        }
        file.close();
        return trips;
    }

    // ==================== RESERVATION CSV OPERATIONS ====================
    bool saveReservation(int userId, int tripId, const string& seats) {
        ofstream file(dataDir + "reservations.csv", ios::app);
        if (!file.is_open()) {
            // Create header if file doesn't exist
            ofstream newFile(dataDir + "reservations.csv");
            newFile << "UserID,TripID,Seats,ReservationDate" << endl;
            newFile.close();
            file.open(dataDir + "reservations.csv", ios::app);
        }

        string date = __DATE__;
        file << userId << ","
             << tripId << ","
             << escapeCSVField(seats) << ","
             << date << endl;

        cout << "Reservation saved." << endl;
        file.close();
        return true;
    }

    // ==================== QR CODE HELPER ====================
    bool generateQRTextFile(const string& busLine, const string& busType, 
                           const string& time, const string& seats, const string& price) {
        ofstream file("QR.txt");
        if (!file.is_open()) {
            cerr << "Cannot create QR.txt" << endl;
            return false;
        }

        file << "Bus_line:" << busLine << endl;
        file << "Bus_type:" << busType << endl;
        file << "Time:" << time << endl;
        file << "Seats:" << seats << endl;
        file << "price:" << price << endl;

        file.close();
        return true;
    }

    vector<vector<string>> searchTrips(const string& busLine) {
        vector<vector<string>> results;
        ifstream file(dataDir + "Trips.csv");
        if (!file.is_open()) return results;

        string line;
        getline(file, line); // Skip header
        while (getline(file, line)) {
            vector<string> fields = parseCSVLine(line);
            if (!fields.empty() && fields[0] == busLine) {
                results.push_back(fields);
            }
        }
        file.close();
        return results;
    }
};
