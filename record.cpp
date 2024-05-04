#include "record.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <filesystem>

void Record::create(const std::string& tableName, const std::string& columnName, const std::string& value) {
    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::cout << "Creating record in " << rowPath << " with value " << value << std::endl;
    std::ofstream outFile(rowPath, std::ios_base::app); 
    if (outFile.is_open()) {
        outFile << value << std::endl;
        std::cout << "Record created successfully." << std::endl;
        outFile.close();
    } else {
        std::cerr << "Error: Unable to create record file." << std::endl;
    }
}


void Record::createView() {
    Record record; 
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cerr << "Error: User not logged in." << std::endl;
        return;
    }
    if (!Globals::getInstance()->checkForDatabase()) {
        return;
    }
    std::string tableName;
    std::cout << "Enter table name: ";
    std::cin >> tableName; 
    std::string columnName;
    std::cout << "Enter column name: ";
    std::cin >> columnName;

    if (!Globals::getInstance()->checkForTable(tableName)) {
        std::cerr << "Error: Table does not exist." << std::endl;
        return;  
    }  
    if (!Globals::getInstance()->checkForRow(tableName, columnName)) {
        std::cerr << "Error: Row does not exist." << std::endl;
        return;
    }
    std::cout << "Enter records, 'exit' to finish" << std::endl;
    for (std::string value; std::cin >> value && value != "exit";) {
        record.create(tableName, columnName, value);
    }
}

void Record::deleteView() {
    Record record;
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cerr << "Error: User not logged in." << std::endl;
        return;
    }
    if (!Globals::getInstance()->checkForDatabase()) {
        return;
    }
    std::string tableName;
    std::cout << "Enter table name: ";
    std::cin >> tableName; 
    
    if (!Globals::getInstance()->checkForTable(tableName)) {
        std::cerr << "Error: Table does not exist." << std::endl;
        return;
    }  
    
    std::string columnName;
    std::cout << "Enter column name: ";
    std::cin >> columnName;
    record.deleteRecord(tableName, columnName);
}





void Record::deleteRecord(const std::string& tableName, const std::string& columnName) {
    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::string tempPath = rowPath + ".tmp";

    std::cout << "Row path: " << rowPath << std::endl; // Print rowPath for debugging

    std::ifstream inFile(rowPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open row file." << std::endl;
        return;
    }

    std::string selectedLine = readRecordSelector(tableName, columnName);
    if (selectedLine.empty()) {
        std::cerr << "Error: Selected line is empty." << std::endl; // Print error message for debugging
        return;
    }

    std::cout << "Selected line: " << selectedLine << std::endl; // Print selectedLine for debugging

    std::ofstream outFile(tempPath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open temp file." << std::endl;
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        std::cout << "Reading line: " << line << std::endl; // Print each line for debugging
        if (line != selectedLine) {
            outFile << line << std::endl;
        }
    }

    inFile.close();
    outFile.close();

    if (std::remove(rowPath.c_str()) != 0) {
        std::cerr << "Error: Unable to remove original row file." << std::endl;
        return;
    }

    if (std::rename(tempPath.c_str(), rowPath.c_str()) != 0) {
        std::cerr << "Error: Unable to rename temp file." << std::endl;
        return;
    }

    std::cout << "Record deleted successfully." << std::endl;
}



















std::string Record::readRecordSelector(const std::string& tableName, const std::string& columnName) {
    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::ifstream inFile(rowPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open row file." << std::endl;
        return "";
    }

    std::string line;
    std::string selectedLine;
    int selection = 0;
    int i = 1; // Start from 1
    while (std::getline(inFile, line)) {
        if (i == selection) { // Compare against selection directly
            selectedLine = line;
        }
        if (i > 10 && selection <= 10) {
            std::cout << "..." << std::endl;
            break;
        }
        std::cout << i << ". " << line << std::endl;
        i++;
    }
    inFile.close();

    if (i == 1) { // Check if no records found
        std::cout << "No records found." << std::endl;
        return "";
    }

    while (true) {
        std::cout << "Select record (1-" << i - 1 << "):" << std::endl;
        std::cin >> selection;
        if (selection >= 1 && selection <= i - 1) { // Adjust upper bound
            break;
        }
        std::cout << "Invalid selection, please try again." << std::endl;
    }

    return selectedLine;
}







