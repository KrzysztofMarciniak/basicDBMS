#ifndef TABLE_H
#define TABLE_H

#include <string>

class Table {
public:
    Table(const std::string& databaseName, const std::string& tableName);
    static void createTableView();
    static bool checkForDatabase();
    static void createTable(const std::string& tableName);
    static void deleteTable(const std::string& tableName);
    static void deleteTableView();
    static void listTables();
    static void printExistingTables(const std::string& databasePath);
private:
    std::string name;
    std::string path;
};

#endif
