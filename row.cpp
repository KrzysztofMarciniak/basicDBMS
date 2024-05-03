#include "row.h"
#include "table.h"
#include <iostream>
#include <fstream>
#include <algorithm>

Row::Row(Table* tableInstance) : tableInstance(tableInstance) {}

void Row::addRowView() {
    if (!tableInstance->checkForDatabase()) {
        return;
    }
    std::string tableName, columnName, columnType;
    std::cout << "Enter table name: ";
    std::cin >> tableName;

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
    if (!tableInstance->isValidTableName(tableName)) {
        std::cerr << "Error: Invalid table name." << std::endl;
        return;
    }

    std::string fileName = tableName + "/" + columnName + ".row." + columnType + ".bdbms";
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
