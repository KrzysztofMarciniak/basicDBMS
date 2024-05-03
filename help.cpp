#include "help.h"
#include <iostream>
#include <fstream>
#include <sstream>

void Help::help() {
    std::vector<std::string> commands = helpFinder("command_registration.h");
    std::cout << "\n Available commands:" << std::endl;
    for (const auto& command : commands) {
        std::cout << "  - " << command << std::endl;
    }
    std::cout<<"\n";
}


std::vector<std::string> Help::helpFinder(const std::string& filename) {
    std::vector<std::string> commands;
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find("interface.registerCommand");
            if (pos != std::string::npos) {
                size_t start = line.find('"', pos);
                size_t end = line.find('"', start + 1);
                if (start != std::string::npos && end != std::string::npos) {
                    std::string command = line.substr(start + 1, end - start - 1);
                    commands.push_back(command);
                }
            }
        }
        file.close();
    } else {
        std::cerr << "Unable to open file: " << filename << std::endl;
    }
    return commands;
}
