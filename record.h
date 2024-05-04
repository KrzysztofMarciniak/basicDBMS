#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <vector>

class Record {
public:
    static void createView();
    static void deleteView();
    static void readView();
    static void readRecordsView();
private:
    void deleteRecord(const std::string& tableName, const std::string& columnName);
    std::string readRecordSelector(const std::string &tableName, const std::string &columnName);
    void read(const std::string &tableName, const std::string &columnName, const std::string &value);
    void create(const std::string& tableName, const std::string& columnName, const std::string& value);
    static std::vector<std::string> readRecords(const std::string& tableName, const std::string& columnName);
};

#endif 
