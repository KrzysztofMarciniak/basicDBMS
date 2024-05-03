#include "globals.h"
#include <sys/stat.h>
#include <iostream>
#include <filesystem>

Globals* Globals::instance = nullptr;

bool Globals::checkForDatabase() {
    std::string databasePath = getDatabasePath();
    struct stat info;
    if (stat(databasePath.c_str(), &info) != 0 || !(info.st_mode & S_IFDIR)) {
        std::cout << "Error: Database folder does not exist." << std::endl;
        return false;
    }
    return true;
}

bool Globals::checkForTable(const std::string& tableName) {
    std::string tablePath = getTablePath(tableName);
    return std::filesystem::exists(tablePath) && std::filesystem::is_directory(tablePath);
}
    
Globals* Globals::getInstance() {
    if (!instance) {
        instance = new Globals();
    }
    return instance;
}

void Globals::setLoggedIn(bool status) {
    loggedIn = status;
}

bool Globals::isLoggedIn() const {
    return loggedIn;
}

void Globals::setUsername(const std::string& username) {
    loggedInAs = username;
}

std::string Globals::getUsername() const {
    return loggedInAs;
}

std::string Globals::getTablePath(const std::string& tableName) const {
    return getDatabasePath() + tableName + ".table/";
}
std::string Globals::getDatabasePath() const {
    return loggedInAs + "Database/";
}

