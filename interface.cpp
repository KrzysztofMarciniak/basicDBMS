#include "interface.h"
#include <iostream>

Interface::Interface() {}

void Interface::registerCommand(const std::string& command, CommandFunction function) {
    commandMap[command] = function;
}

void Interface::executeCommand(const std::string& command) {
    auto it = commandMap.find(command);
    if (it != commandMap.end()) {
        it->second();
    } else {
        std::cout << "\033[1;31mCommand not found: " << command << "\033[0m" << std::endl;
    }
}
