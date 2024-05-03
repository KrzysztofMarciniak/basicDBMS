#include "user.h"
#include "globals.h"
#include "logs.h"
#include <fstream>
#include <iostream>
User::User(const std::string& username, const std::string& password)
    : username(username), password(password) {}


void User::createView() {
    std::string username, password, confirmPassword;
    std::cout << "Enter username: ";
    std::cin >> username;
    
    std::cout << "Enter password: ";
    std::cin >> password;
    std::cout << "Confirm password: ";
    std::cin >> confirmPassword;

    if (password != confirmPassword) {
        std::cout << "Passwords do not match. User creation failed." << std::endl;
        return;
    }

    User::create(username, password);
}

void User::create(const std::string& username, const std::string& password) {
    std::ofstream file("creds.bdbms", std::ios::app);
    if (file.is_open()) {
        file << username << " " << password << std::endl;
        file.close();
        std::cout << "User created successfully." << std::endl;
        Logs::log("User '" + username + "' created successfully.");
    } else {
        std::cout << "Failed to open file for writing." << std::endl;
        Logs::log("Failed to create user '" + username + "': Failed to open file for writing.");
    }
}

void User::readView() {
    std::string username;
    std::cout << "Enter username to view: ";
    std::cin >> username;
    User::read(username);
}
void User::logout() {
    if (Globals::getInstance()->isLoggedIn()) {
        std::string username = Globals::getInstance()->getUsername();
        Globals::getInstance()->setLoggedIn(false); 
        Globals::getInstance()->setUsername(""); 
        Logs::log(username + " Logged out.");

        std::cout << "Logged out successfully." << std::endl;
    } else {
        std::cout << "Error: No user logged in." << std::endl;
        Logs::log("Someone tried to logout while not being logged in.");
    }
}

void User::whoami() {
    std::string username = Globals::getInstance()->getUsername();
    if (Globals::getInstance()->isLoggedIn()) {
        std::cout << "Logged in as: " << username << std::endl;
        Logs::log(username + " checked their own username.");
    } else {
        std::cout << "Not logged in." << std::endl;
        Logs::log("Someone tried to check their own username.");
    }
}

bool User::login(const std::string& username, const std::string& password) {
    std::ifstream file("creds.bdbms");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string user = line.substr(0, pos);
            std::string pass = line.substr(pos + 1);
            if (user == username && pass == password) {
                file.close();
                Globals::getInstance()->setLoggedIn(true);
                Globals::getInstance()->setUsername(username);
                Logs::log(username + " logged in");
                return true;
            }
        }
    }
    file.close();
    Logs::log(username + " failed to login in");
    return false;
}

void User::loginView() {
    std::string username, password;
    std::cout << "Enter username: ";
    std::cin >> username;
    std::cout << "Enter password: ";
    std::cin >> password;
    if (User::login(username, password)) {
        std::cout << "Login successful." << std::endl;
    } else {
        std::cout << "Invalid username or password." << std::endl;
    }
}
void User::read(const std::string& username) {
    std::ifstream file("creds.bdbms");
    std::string line;
    bool found = false;
    while (std::getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string user = line.substr(0, pos);
            std::string pass = line.substr(pos + 1);
            if (user == username) {
                std::cout << "Username: " << user << ", Password: " << pass << std::endl;
                found = true;
                break;
            }
        }
    }
    if (!found) {
        std::cout << "User not found." << std::endl;
    }
}

void User::del(const std::string& username) {
    std::ifstream inFile("creds.bdbms");
    std::ofstream outFile("temp.bdbms");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error: Unable to open files." << std::endl;
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string user = line.substr(0, pos);
            if (user != username) {
                outFile << line << std::endl;
            } else {
                found = true;
            }
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("creds.bdbms");
        rename("temp.bdbms", "creds.bdbms");
        std::cout << "User deleted successfully." << std::endl;
    } else {
        std::cout << "User not found." << std::endl;
        remove("temp.bdbms");
    }
}
void User::update(const std::string& username, const std::string& newPassword) {
    std::ifstream inFile("creds.bdbms");
    std::ofstream outFile("temp.bdbms");

    if (!inFile.is_open() || !outFile.is_open()) {
        std::cerr << "Error: Unable to open files." << std::endl;
        return;
    }

    std::string line;
    bool found = false;
    while (std::getline(inFile, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string user = line.substr(0, pos);
            std::string pass = line.substr(pos + 1);
            if (user == username) {
                outFile << user << " " << newPassword << std::endl;
                found = true;
            } else {
                outFile << line << std::endl;
            }
        }
    }

    inFile.close();
    outFile.close();

    if (found) {
        remove("creds.bdbms");
        rename("temp.bdbms", "creds.bdbms");
        std::cout << "Password updated successfully." << std::endl;
        Logs::log("Password for user '" + username + "' updated successfully.");
    } else {
        std::cout << "User not found." << std::endl;
        Logs::log("Failed to update password for user '" + username + "': User not found.");
        remove("temp.bdbms");
    }
}

void User::updateView() {
    std::string username, newPassword;
    std::cout << "Enter username to update: ";
    std::cin >> username;
    std::cout << "Enter new password: ";
    std::cin >> newPassword;
    User::update(username, newPassword);
}

void User::delView() {
    std::string username;
    std::cout << "Enter username to delete: ";
    std::cin >> username;
    User::del(username);
}

void User::listAll() {
    std::ifstream file("creds.bdbms");
    std::string line;
    while (std::getline(file, line)) {
        size_t pos = line.find(' ');
        if (pos != std::string::npos) {
            std::string user = line.substr(0, pos);
            std::string pass = line.substr(pos + 1);
            std::cout << "Username: " << user << ", Password: " << pass << std::endl;
        }
    }
    file.close();
}
