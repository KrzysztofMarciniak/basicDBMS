#include "globals.h"

Globals* Globals::instance = nullptr;

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

std::string Globals::getDatabasePath() const {
    return loggedInAs + "Database/";
}
