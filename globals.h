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
    void setUsername(const std::string& username);
    std::string getUsername() const; 
    std::string getDatabasePath() const; 


};

#endif
