#include "database.h"
#include "globals.h" 

#include <iostream>
#include <sys/stat.h>

void Database::createDatabase(const std::string& username) {
    if (!Globals::getInstance()->isLoggedIn()) {
        std::cout << "Error: User not logged in." << std::endl;
        return;
    }

    std::string directory = username + "Database";
    int status = mkdir(directory.c_str(), 0777);
    if (status == -1) {
        std::cerr << "Error: Failed to create database directory." << std::endl;
        return;
    }

    std::cout << "Database created successfully." << std::endl;
}
void Database::createDatabaseView() {
    std::string username = Globals::getInstance()->getUsername();
    Database::createDatabase(username);
}