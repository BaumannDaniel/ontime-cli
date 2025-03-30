#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "logging.h"

ToneLogger::ToneLogger(const std::string &filename) {
    log_file.open(filename, std::ios::app);
    if (!log_file.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
    }
}

ToneLogger::~ToneLogger() {
    log_file.close();
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
    log_mutex.lock();
    if (log_file.is_open()) {
        log_file << logEntry.str();
        log_file.flush();
    }
    log_mutex.unlock();
}
