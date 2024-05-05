#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    std::string username;
    std::string password;

    User(const std::string& username, const std::string& password);
    static void createView();
    static void readView();
    static void create(const std::string& username, const std::string& password);
    static void read(const std::string& username);
    static void del(const std::string& username);
    static void delView();
    static void update(const std::string& username, const std::string& newPassword);
    static void updateView();
    static bool login(const std::string& username, const std::string& password);
    static void loginView();
    static void logout();
    static void whoami();
    static void listAll();
};

#endif
