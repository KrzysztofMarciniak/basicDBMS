#include "logs.h"
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>

void Logs::log(const std::string& message) {
    auto now = std::chrono::system_clock::now();
    std::time_t now_time = std::chrono::system_clock::to_time_t(now);
    std::string timeString = std::ctime(&now_time);

    timeString.pop_back();

    std::ofstream logfile("basicDBMS.logs.txt", std::ios::app);
    if (logfile.is_open()) {
        logfile << "[" << timeString << "] " << message << std::endl;
        logfile.close();
    } else {
        std::cerr << "Error: Unable to open log file." << std::endl;
    }
}
