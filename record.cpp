#include "record.h"
#include "globals.h"
#include <iostream>
#include <fstream>
#include <filesystem>
#include <vector>

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




std::string Record::readRecordSelector(const std::string& tableName, const std::string& columnName) {
    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::ifstream inFile(rowPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open row file." << std::endl;
        return "";
    }

    std::vector<std::string> lines;
    std::string line;
    int i = 1;
    while (std::getline(inFile, line)) {
        lines.push_back(line);
        std::cout << i << ". " << line << std::endl;
        i++;
    }

    inFile.close();

    if (lines.empty()) {
        std::cout << "No records found." << std::endl;
        return "";
    }

    int selection;
    while (true) {
        std::cout << "Select record (1-" << lines.size() << "): ";
        std::cin >> selection;
        if (selection >= 1 && selection <= lines.size()) {
            break;
        }
        std::cout << "Invalid selection, please try again." << std::endl;
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    return lines[selection - 1]; 
}


void Record::deleteRecord(const std::string& tableName, const std::string& columnName) {
    std::string selectedLine = readRecordSelector(tableName, columnName);
    if (selectedLine.empty()) {
        return;
    }

    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::string tempPath = rowPath + ".tmp";

    std::ifstream inFile(rowPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open row file." << std::endl;
        return;
    }

    std::ofstream outFile(tempPath);
    if (!outFile.is_open()) {
        std::cerr << "Error: Unable to open temp file." << std::endl;
        inFile.close();
        return;
    }

    std::string line;
    while (std::getline(inFile, line)) {
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

std::vector<std::string> Record::readRecords(const std::string& tableName, const std::string& columnName) {
    std::vector<std::string> records;

    std::string rowPath = Globals::getInstance()->getRowPath(tableName, columnName);
    std::ifstream inFile(rowPath);
    if (!inFile.is_open()) {
        std::cerr << "Error: Unable to open row file." << std::endl;
        return records;
    }

    std::string line;
    while (std::getline(inFile, line)) {
        records.push_back(line);
    }

    inFile.close();

    if (records.empty()) {
        std::cout << "No records found." << std::endl;
    } else {
        std::cout << "Records:" << std::endl;
        for (const auto& record : records) {
            std::cout << record << std::endl;
        }
    }

    return records;
}
void Record::readRecordsView() {
    if (!Globals::getInstance()->checkForDatabase()) {
        return;
    }    
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cerr << "Error: User not logged in." << std::endl;
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
    
    std::vector<std::string> records = Record::readRecords(tableName, columnName);
}
