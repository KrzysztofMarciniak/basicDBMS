#ifndef RECORD_H
#define RECORD_H

#include <string>

class Record {
public:
    static void createView();
    static void deleteView();
    static void readView();
private:
    void deleteRecord(const std::string& tableName, const std::string& columnName);
    std::string readRecordSelector(const std::string &tableName, const std::string &columnName);
    void read(const std::string &tableName, const std::string &columnName, const std::string &value);
    void create(const std::string& tableName, const std::string& columnName, const std::string& value);
};

#endif 
