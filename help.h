#ifndef HELP_H
#define HELP_H

#include <vector>
#include <string>

class Help {
public:
    static void help();
    static std::vector<std::string> helpFinder(const std::string& filename);
};

#endif
