#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "logging.h"

ToneLogger::ToneLogger(const std::string &filename) {
    logFile.open(filename, std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
    }
}

ToneLogger::~ToneLogger() {
    logFile.close();
}

void ToneLogger::log(const std::string &message) {
    time_t now = time(nullptr);
    tm *timeInfo = localtime(&now);
    char timestamp[20];
    strftime(
        timestamp,
        sizeof(timestamp),
        "%Y-%m-%d %H:%M:%S",
        timeInfo
    );

    // Create log entry
    std::ostringstream logEntry;
    logEntry << "[" << timestamp << "] " << message << std::endl;
    if (logFile.is_open()) {
        logFile << logEntry.str();
        logFile.flush();
    }
}
