#ifndef ROW_H
#define ROW_H

#include "globals.h"
#include <iostream>
#include <fstream>
#include <algorithm>
#include <filesystem>

class Row {
public:
    static void addRowView();
    static void deleteRowView();

private:
    static void addRow(const std::string& tableName, const std::string& columnName, const std::string& columnType);
    static void deleteRow(const std::string& tableName, const std::string& columnName);
    static bool isValidColumnType(const std::string& columnType);
};

#endif // ROW_H
