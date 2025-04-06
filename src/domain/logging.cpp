#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include "logging.h"

tone::DebugLogger::DebugLogger(const std::string &filename) {
    log_file_.open(filename, std::ios::app);
    if (!log_file_.is_open()) {
        std::cerr << "Error opening log file." << std::endl;
    }
}

tone::DebugLogger::~DebugLogger() {
    log_file_.close();
}

void tone::DebugLogger::log(const std::string &message) {
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
    log_mutex_.lock();
    if (log_file_.is_open()) {
        log_file_ << logEntry.str();
        log_file_.flush();
    }
    log_mutex_.unlock();
}

void tone::ReleaseLogger::log(const std::string &message) {
}
