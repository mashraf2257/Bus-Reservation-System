# Bus Reservation System

A C++ based bus reservation system with SQL Server database integration for managing bus tickets, routes, trips, and user accounts.

## 📋 Table of Contents
- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Requirements](#requirements)
- [Installation](#installation)
- [Database Configuration](#database-configuration)
- [Usage](#usage)
- [Class Architecture](#class-architecture)
- [Contributing](#contributing)

## 🚀 Overview

This Bus Reservation System is a console-based application developed in C++ that provides functionality for managing bus reservations, routes, trips, and user authentication. The system uses SQL Server as its backend database through the ODBC interface via the nanodbc library.

## ✨ Features

- **User Management**: User registration and authentication system
- **Bus Management**: Add, update, and manage bus information including capacity and drivers
- **Route Management**: Define and manage bus routes
- **Trip Management**: Schedule and manage bus trips
- **Database Integration**: Automated database creation and schema management
- **ODBC Connectivity**: Reliable database connection using nanodbc library

## 📁 Project Structure

```
Bus-Reservation-System/
├── src/                    # Source files (.cpp)
│   ├── main.cpp           # Main entry point
│   ├── bus.cpp            # Bus class implementation
│   ├── route.cpp          # Route class implementation
│   ├── trip.cpp           # Trip class implementation
│   └── user.cpp           # User class implementation
├── include/               # Header files (.h)
│   ├── database.h         # Database connection and schema
│   ├── datamigration.h    # Data migration utilities
│   ├── login.h            # Authentication logic
│   ├── bus.h              # Bus class definition
│   ├── route.h            # Route class definition
│   ├── trip.h             # Trip class definition
│   └── user.h             # User class definition
├── lib/                   # External libraries
│   ├── nanodbc/          # nanodbc library folder
│   ├── nanodbc.cpp       # nanodbc implementation
│   └── nanodbc.h         # nanodbc header
├── bin/                   # Compiled executables
│   └── program.exe        # Main executable
├── output/                # Build output directory
├── docs/                  # Documentation
│   └── problems.txt       # Known issues and notes
└── README.md             # This file
```

## 🛠️ Requirements

### Software Requirements
- **C++ Compiler**: Visual Studio 2019 or later (MSVC) or MinGW-w64
- **SQL Server**: Microsoft SQL Server (any edition)
- **ODBC Driver**: ODBC Driver 17 for SQL Server or later
- **Operating System**: Windows (configured for Windows ODBC)

### Libraries
- **nanodbc**: Modern C++ wrapper for ODBC (included in lib/)

## 📦 Installation

1. **Clone the repository**
   ```bash
   git clone https://github.com/yourusername/Bus-Reservation-System.git
   cd Bus-Reservation-System
   ```

2. **Install SQL Server ODBC Driver**
   - Download and install [ODBC Driver 17 for SQL Server](https://docs.microsoft.com/en-us/sql/connect/odbc/download-odbc-driver-for-sql-server)

3. **Set up SQL Server**
   - Ensure SQL Server is running on your machine
   - Note your server name (default in code: `Bola`)

4. **Compile the project**
   ```bash
   # Using Visual Studio
   # Open the project in Visual Studio and build
   
   # Or using g++ (if configured)
   g++ -o bin/program.exe src/*.cpp lib/nanodbc.cpp -I include -I lib -std=c++17
   ```

## 🗄️ Database Configuration

The system automatically creates the database and tables on first run. The database configuration is in `include/database.h`:

- **Database Name**: `BRSYS`
- **Server**: Configurable (default: `Bola`)
- **Authentication**: Windows Trusted Connection

### Database Schema

The system creates the following tables:
- `app_user`: User accounts with ID starting from 1000000
- `bus`: Bus information
- `route`: Route definitions
- `trip`: Scheduled trips

To modify the server connection:
1. Open `include/database.h`
2. Update the connection string:
   ```cpp
   Server=YOUR_SERVER_NAME;Database=BRSYS;Trusted_Connection=yes;
   ```

## 💻 Usage

1. **Run the executable**
   ```bash
   cd bin
   ./program.exe
   ```

2. **Login/Register**
   - Follow the on-screen prompts to login or register a new account

3. **Navigate the menu**
   - Use the menu system to manage buses, routes, and trips

## 🏗️ Class Architecture

### Core Classes

- **`bus`**: Manages bus entities with driver, capacity, and route information
- **`route`**: Defines bus routes with source and destination
- **`trip`**: Handles scheduled trips on specific routes
- **`user`**: User account management
- **`DB`**: Database connection and initialization
- **`log`**: Authentication and login functionality

### Key Design Patterns
- Object-Oriented Design with encapsulation
- Database abstraction layer
- Separation of concerns (headers/implementation)

## 🐛 Known Issues

See [docs/problems.txt](docs/problems.txt) for current known issues and development notes.

## 🤝 Contributing

Contributions are welcome! Please follow these steps:

1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

## 📄 License

This project is developed as part of academic coursework at Nile University.

## 👤 Author

**Bola Gerges**
- University: Nile University

## 📞 Support

For support or questions, please create an issue in the repository.

---

**Note**: Make sure to update the database connection settings in `include/database.h` according to your SQL Server configuration before running the application.
