#pragma once
#include <iostream>
#include "csvmanager.h"

using namespace std;

class DB {
private:
    CSVManager csvManager;

public:
    DB() {
        // CSV Manager is initialized automatically
        // Data files (users.csv, routes.csv, buses.csv, trips.csv, reservations.csv) 
        // are created automatically if they don't exist
        cout << "Database initialized using CSV files in data/ folder" << endl;
    }

    // Get the CSV Manager instance
    CSVManager& getCSVManager() {
        return csvManager;
    }
};