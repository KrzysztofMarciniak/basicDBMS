#ifndef RECORDS_H
#define RECORDS_H

#include <string>

class Records {
public:
    static void addRecordView();
    static void addRecord(const std::string& tableName);

    static void printTable(const std::string& tableName);
    static void printTableView();
};

#endif
