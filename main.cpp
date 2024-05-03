#include <iostream>
#include "interface.h"
#include "user.h"
#include "command_registration.h"
int main() {
    Interface interface;

    registerCommands(interface);

    while (true) {
        std::string command;
        std::cout << "Enter command: ";
        std::cin >> command;
        if (command == "exit") {
            break;
        }
        interface.executeCommand(command);
    }

    return 0;
}
