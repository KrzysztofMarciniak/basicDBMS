#ifndef GLOBALS_H
#define GLOBALS_H

#include <string>

class Globals {
private:
    Globals() {} 
    static Globals* instance;

    bool loggedIn = false;
    std::string loggedInAs;

public:
    static Globals* getInstance();
    void setLoggedIn(bool status);
    bool isLoggedIn() const;
    bool checkForDatabase();
    void setUsername(const std::string& username);
    bool checkForRow(const std::string& tableName, const std::string& columnName);
    bool checkForTable(const std::string& tableName);
    std::string getUsername() const; 
    std::string getDatabasePath() const; 
    std::string getTablePath(const std::string& tableName) const;
    std::string getRowPath(const std::string& tableName, const std::string& columnName) const;  
};

#endif
