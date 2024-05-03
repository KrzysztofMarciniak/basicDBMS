#include "row.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

void Row::addRowView() {
    
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cerr << "Error: User not logged in." << std::endl;
        return;
    }
    if (!Globals::getInstance()->checkForDatabase()) {
        return;
    }

    std::string tableName, columnName, columnType;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

    if (!Globals::getInstance()->checkForTable(tableName)) {
        std::cerr << "Error: Table does not exist." << std::endl;
        return;
    }

    std::cout << "Enter column name: ";
    std::cin >> columnName;
    std::cout << "Enter column type (TEXT, BOOLEAN, INT): ";
    std::cin >> columnType;

    std::transform(columnType.begin(), columnType.end(), columnType.begin(), ::toupper);

    if (!isValidColumnType(columnType)) {
        std::cerr << "Error: Invalid column type. Please enter TEXT, BOOLEAN, or INT." << std::endl;
        return;
    }

    addRow(tableName, columnName, columnType);
}

void Row::addRow(const std::string& tableName, const std::string& columnName, const std::string& columnType) {
    std::string tablePath = Globals::getInstance()->getTablePath(tableName);
    std::string fileName = tablePath + columnName + ".row." + columnType + ".bdbms";
    std::ofstream outFile(fileName);
    if (outFile.is_open()) {
        std::cout << "Row file '" << fileName << "' created successfully." << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error: Unable to create row file." << std::endl;
    }
}

bool Row::isValidColumnType(const std::string& columnType) {
    return (columnType == "TEXT" || columnType == "BOOLEAN" || columnType == "INT");
}

void Row::deleteRowView() {
    
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cerr << "Error: User not logged in." << std::endl;
        return;
    }
    if (!Globals::getInstance()->checkForDatabase()) {
        return;
    }

    std::string tableName, columnName;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

    if (!Globals::getInstance()->checkForTable(tableName)) {
        std::cerr << "Error: Table does not exist." << std::endl;
        return;
    }

    std::cout << "Enter column name: ";
    std::cin >> columnName;

    deleteRow(tableName, columnName);
}

void Row::deleteRow(const std::string& tableName, const std::string& columnName) {
    std::string tablePath = Globals::getInstance()->getTablePath(tableName);
    std::filesystem::directory_iterator end_itr;
    for (std::filesystem::directory_iterator itr(tablePath); itr != end_itr; ++itr) {
        if (itr->is_regular_file() && itr->path().filename().string().find(columnName) == 0) {
            if (std::filesystem::remove(itr->path())) {
                std::cout << "Row '" << itr->path().filename() << "' deleted successfully." << std::endl;
            } else {
                std::cerr << "Error: Unable to delete row '" << itr->path().filename() << "'." << std::endl;
            }
            return;
        }
    }
    std::cerr << "Error: Row file not found." << std::endl;
}
