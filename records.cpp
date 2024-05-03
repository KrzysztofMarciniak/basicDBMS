#include "records.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <filesystem>

namespace fs = std::filesystem;

void Records::printTableView(){
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }
    std::string tableName;
    std::cout << "Enter the name of the table: ";
    std::cin >> tableName;
    printTable(tableName);
}
void Records::printTable(const std::string& tableName) {
    std::string username = Globals::getInstance()->getUsername();
    std::string databasePath = username + "Database/";

    std::string filePath = databasePath + tableName + ".table.bdbms";

    if (!fs::exists(filePath)) {
        std::cout << "No table found. Create a table using createTable command." << std::endl;
        return;
    }

    std::ifstream tableFile(filePath);
    if (!tableFile.is_open()) {
        std::cout << "Failed to open table file." << std::endl;
        return;
    }

    std::cout << "Contents of table '" << tableName << "':" << std::endl;
    std::string line;
    while (std::getline(tableFile, line)) {
        std::cout << line << std::endl;
    }

    tableFile.close();
}

void Records::addRecordView() {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }
    std::string tableName;
    std::cout << "Enter the name of the table: ";
    std::cin >> tableName;
    addRecord(tableName);
}

void Records::addRecord(const std::string& tableName) {
    std::string username = Globals::getInstance()->getUsername();
    std::string databasePath = username + "Database/";

    std::string filePath = databasePath + tableName + ".table.bdbms";

    if (!fs::exists(filePath)) {
        std::cout << "No table found. Create a table using createTable command." << std::endl;
        return;
    }

    std::ofstream tableFile(filePath, std::ios_base::app);
    if (!tableFile.is_open()) {
        std::cout << "Failed to open table file." << std::endl;
        return;
    }

    std::ifstream inFile(filePath);
    int nextId = 1;
    std::string line;
    while (std::getline(inFile, line)) {
        ++nextId;
    }

    std::string record;
    std::cout << "Enter record (type 'exit' to quit): ";
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); 
    while (true) {
        std::getline(std::cin, record);
        if (record == "exit") {
            break;
        }
        if (record.find_first_not_of(' ') != std::string::npos) {
            tableFile << nextId++ << "." << record << std::endl;
            std::cout << "Record added successfully. Enter another record (type 'exit' to quit): ";
        } else {
            std::cout << "Error: Record cannot be empty. Please enter a valid record." << std::endl;
        }
    }

    tableFile.close();
}
