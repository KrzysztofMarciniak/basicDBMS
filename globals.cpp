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

bool Globals::checkForRow(const std::string& tableName, const std::string& columnName) {
    std::cout << "Checking for row in table " << tableName << " with column name " << columnName << std::endl;
    std::filesystem::directory_iterator end_itr;
    for (std::filesystem::directory_iterator itr(getTablePath(tableName)); itr != end_itr; ++itr) {
        std::cout << "Checking file " << itr->path().filename().string() << std::endl;
        if (itr->is_regular_file() && itr->path().filename().string().find(columnName) == 0) {
            std::cout << "Found matching row file" << std::endl;
            return true;
        }
    }
    std::cout << "No matching row file found" << std::endl;
    return false;
}
std::string Globals::getRowPath(const std::string& tableName, const std::string& columnName) const {
    std::filesystem::directory_iterator end_itr;
    for (std::filesystem::directory_iterator itr(getTablePath(tableName)); itr != end_itr; ++itr) {
        if (itr->is_regular_file() && itr->path().filename().string().find(columnName) == 0) {
            return itr->path().string();
        }
    }
    throw std::runtime_error("No row file found for given column name");
}








