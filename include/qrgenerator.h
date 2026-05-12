#pragma once
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <cstdlib>

using namespace std;

class QRGenerator {
private:
    string outputDir = "./";

public:
    QRGenerator() = default;

    // Generate QR code as text file for web display
    bool generateQRText(const string& reservationData, const string& outputFile = "QR.txt") {
        ofstream file(outputFile);
        if (!file.is_open()) {
            cerr << "Failed to create QR text file." << endl;
            return false;
        }

        file << reservationData;
        file.close();

        cout << "QR data text file generated: " << outputFile << endl;
        return true;
    }

    // Generate QR code using command line tool (requires qr library installed)
    // Install: pip install qrcode[pil]
    bool generateQRCodeImage(const string& data, const string& outputFile = "ticket_qr.png") {
        string command = "python -m qrcode \"" + data + "\" -o " + outputFile;
        
        int result = system(command.c_str());
        if (result != 0) {
            cerr << "Failed to generate QR code image. Make sure Python and qrcode library are installed." << endl;
            return false;
        }

        cout << "QR code generated: " << outputFile << endl;
        return true;
    }

    // Format reservation data for QR/ticket display
    string formatReservationData(const string& busLine, const string& busType,
                                const string& time, const vector<string>& seats,
                                const string& price) {
        ostringstream oss;
        oss << "Bus_line:" << busLine << "\n";
        oss << "Bus_type:" << busType << "\n";
        oss << "Time:" << time << "\n";
        oss << "Seats:";
        
        for (size_t i = 0; i < seats.size(); i++) {
            if (i > 0) oss << ";";
            oss << seats[i];
        }
        oss << "\n";
        oss << "price:" << price << "\n";

        return oss.str();
    }

    // Display ticket in console
    void displayTicketConsole(const string& busLine, const string& busType,
                             const string& time, const vector<string>& seats,
                             const string& price) {
        cout << "\n=====================================" << endl;
        cout << "         YOUR BOOKING TICKET          " << endl;
        cout << "=====================================" << endl;
        cout << "Bus Line: " << busLine << endl;
        cout << "Bus Type: " << busType << endl;
        cout << "Departure Time: " << time << endl;
        cout << "Booked Seats: ";
        for (size_t i = 0; i < seats.size(); i++) {
            if (i > 0) cout << ", ";
            cout << seats[i];
        }
        cout << endl;
        cout << "Price: EGP " << price << endl;
        cout << "=====================================" << endl;
        cout << "Scan the QR code for digital ticket!" << endl;
        cout << "=====================================" << endl;
    }

    // Generate ticket HTML for web display
    bool generateTicketHTML(const string& busLine, const string& busType,
                           const string& time, const vector<string>& seats,
                           const string& price, const string& htmlFile = "ticket.html") {
        
        // Format seats for HTML display
        string seatsHtml;
        for (size_t i = 0; i < seats.size(); i++) {
            seatsHtml += "<div class=\"seat\">" + seats[i] + "</div>\n";
        }

        string html = R"(<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Bus Ticket</title>
    <style>
        body {
            font-family: 'Arial', sans-serif;
            background-color: #f0f2f5;
            display: flex;
            justify-content: center;
            align-items: center;
            min-height: 100vh;
            margin: 0;
            padding: 20px;
        }
        .ticket {
            width: 100%;
            max-width: 350px;
            background: linear-gradient(135deg, #ffffff, #f8f9fa);
            border-radius: 12px;
            box-shadow: 0 10px 30px rgba(0, 0, 0, 0.1);
            overflow: hidden;
            border: 1px solid #e0e0e0;
        }
        .ticket-header {
            background: linear-gradient(135deg, #4a6bff, #2541b2);
            color: white;
            padding: 15px 20px;
            text-align: center;
        }
        .ticket-header h1 {
            margin: 0;
            font-size: 22px;
            font-weight: 600;
        }
        .ticket-body {
            padding: 20px;
        }
        .ticket-row {
            display: flex;
            justify-content: space-between;
            margin-bottom: 12px;
            padding-bottom: 12px;
            border-bottom: 1px dashed #e0e0e0;
        }
        .ticket-label {
            font-weight: 600;
            color: #666;
            font-size: 14px;
        }
        .ticket-value {
            font-weight: 500;
            color: #333;
            text-align: right;
            font-size: 15px;
        }
        .price {
            font-size: 24px;
            font-weight: 700;
            color: #2541b2;
            text-align: center;
            margin-top: 15px;
            padding-top: 15px;
            border-top: 1px dashed #e0e0e0;
        }
        .seats {
            display: flex;
            flex-wrap: wrap;
            gap: 8px;
            justify-content: flex-end;
        }
        .seat {
            background-color: #4a6bff;
            color: white;
            width: 30px;
            height: 30px;
            border-radius: 4px;
            display: flex;
            align-items: center;
            justify-content: center;
            font-weight: bold;
            font-size: 12px;
        }
    </style>
</head>
<body>
    <div class="ticket">
        <div class="ticket-header">
            <h1>Bus Reservation Ticket</h1>
        </div>
        <div class="ticket-body">
            <div class="ticket-row">
                <div class="ticket-label">Bus Line</div>
                <div class="ticket-value">)" + busLine + R"(</div>
            </div>
            <div class="ticket-row">
                <div class="ticket-label">Bus Type</div>
                <div class="ticket-value">)" + busType + R"(</div>
            </div>
            <div class="ticket-row">
                <div class="ticket-label">Departure Time</div>
                <div class="ticket-value">)" + time + R"(</div>
            </div>
            <div class="ticket-row">
                <div class="ticket-label">Booked Seats</div>
                <div class="seats">
                    )" + seatsHtml + R"(
                </div>
            </div>
            <div class="price">
                EGP )" + price + R"(
            </div>
        </div>
    </div>
</body>
</html>)";

        ofstream file(htmlFile);
        if (!file.is_open()) {
            cerr << "Failed to create ticket HTML file." << endl;
            return false;
        }

        file << html;
        file.close();

        cout << "Ticket HTML generated: " << htmlFile << endl;
        return true;
    }
};
