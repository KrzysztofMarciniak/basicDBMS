#ifndef INTERFACE_H
#define INTERFACE_H

#include <string>
#include <unordered_map>
#include <functional>

class Interface {
public:
    using CommandFunction = std::function<void()>;
    
    Interface();
    void registerCommand(const std::string& command, CommandFunction function);
    void executeCommand(const std::string& command);

private:
    std::unordered_map<std::string, CommandFunction> commandMap;
};

#endif
