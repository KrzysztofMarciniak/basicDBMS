#ifndef DATABASE_H
#define DATABASE_H

#include <string>

class Database {
public:
    static void createDatabase(const std::string& username);
    static void createDatabaseView();
};

#endif
