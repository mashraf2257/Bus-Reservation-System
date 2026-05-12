# Nanodbc / SQL Implementation History

## Overview
During the development of the Bus Reservation System, the team successfully developed a fully functional C++ backend that connected to a SQL database using the `nanodbc` library. This implementation handled users, trips, reservations, and routes using robust relational database paradigms.

## Why it was removed
As the project evolved to include a Graphical User Interface (GUI) built with C++/CLI (Windows Forms), several integration challenges arose:
1. **Complexity:** Bridging the native C++ `nanodbc` library with managed C++/CLI code introduced significant memory management and compilation complexities.
2. **Portability:** Setting up ODBC data sources and ensuring SQL Server was available on every machine made the application harder to distribute and test quickly.
3. **GUI Integration:** The event-driven nature of the Windows Forms GUI required rapid, lightweight reads and writes, which proved easier to implement and debug using a direct file-access approach.

## Resolution
To ensure a stable, portable, and unified application, the team made the architectural decision to pivot from SQL/ODBC to a lightweight CSV-based Data Access Layer (`csvmanager.h` and `datamigration.h`). This allowed the Windows Forms GUI to interact seamlessly with the underlying data without external database dependencies.

The original ODBC implementation has been preserved in the `beta-version/` directory for historical reference and to demonstrate the team's capability to build a full SQL-backed C++ application.
