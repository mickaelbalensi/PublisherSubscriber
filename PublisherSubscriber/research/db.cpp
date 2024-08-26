#include <iostream>
#include <sqlite3.h>

int main() {
    sqlite3* db;
    char* errMsg = 0;
    int rc;

    // Open database
    rc = sqlite3_open("shapes.db", &db);
    if (rc) {
        std::cerr << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
        return 1;
    }

    // Create table
    const char* sql = "CREATE TABLE IF NOT EXISTS Shapes("
                      "ID INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "Type TEXT NOT NULL, "
                      "Area REAL);";
    
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Table created successfully" << std::endl;
    }

    // Insert data
    sql = "INSERT INTO Shapes (Type, Area) VALUES ('Circle', 78.54);";
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if (rc != SQLITE_OK) {
        std::cerr << "SQL error: " << errMsg << std::endl;
        sqlite3_free(errMsg);
    } else {
        std::cout << "Record inserted successfully" << std::endl;
    }

    // Close database
    sqlite3_close(db);
    return 0;
}