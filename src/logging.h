#pragma once
#include <fstream>
#include <mutex>
#include <string>

class ToneLogger {
    std::mutex log_mutex;
    std::ofstream logFile;
public:
    explicit ToneLogger(const std::string& filename);
    ~ToneLogger();
    void log(const std::string& message);
};
