#include "table.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <sys/stat.h> 
#include <filesystem> 
namespace fs = std::filesystem;

Table::Table(const std::string& databaseName, const std::string& tableName) : name(tableName) {
    path = databaseName + "Database/" + tableName + ".bdbms";
}

void Table::listTables() {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }   

    if (!checkForDatabase()) {
        return;
    }

    std::string databasePath = Globals::getInstance()->getDatabasePath();
    printExistingTables(databasePath); 
}



void Table::createTable(const std::string& tableName) {
    std::string databasePath = Globals::getInstance()->getDatabasePath();
    std::string folderPath = databasePath + "/" + tableName + ".table";

    int status = mkdir(folderPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
    if (status == 0) {
        std::cout << "Table '" << tableName << "' created successfully." << std::endl;
    } else {
        std::cout << "Failed to create table." << std::endl;
    }
}



bool Table::checkForDatabase() {
    std::string databasePath = Globals::getInstance()->getDatabasePath();
    struct stat info;
    if (stat(databasePath.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
        std::cout << "Error: Database folder does not exist." << std::endl;
        return false;
    }
    return true;
}

void Table::createTableView() {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }

    if (!checkForDatabase()) {
        return;
    }

    std::string tableName;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

    createTable(tableName);
}
void Table::printExistingTables(const std::string& databasePath) {
    std::cout << "Existing tables:" << std::endl;
    for (const auto& entry : fs::directory_iterator(databasePath)) {
        if (fs::is_directory(entry.path())) {
            std::string folderName = entry.path().filename().string();
            std::cout << "- " << folderName << std::endl;
        }
    }
}



void Table::deleteTable(const std::string& tableName) {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }

    if (!checkForDatabase()) {
        return;
    }

    std::string databasePath = Globals::getInstance()->getDatabasePath();    
    printExistingTables(databasePath); 

    std::string folderPath = databasePath + "/" + tableName + ".table";

    if (std::filesystem::remove_all(folderPath) != 0) {
        std::cout << "Table '" << tableName << "' deleted successfully." << std::endl;
    } else {
        std::cout << "Failed to delete table." << std::endl;
    }
}

void Table::deleteTableView() {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }

    if (!checkForDatabase()) {
        return;
    }

    std::string tableName;
    std::cout << "Enter table name to delete: ";
    std::cin >> tableName;

    deleteTable(tableName);
}