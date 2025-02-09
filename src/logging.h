#pragma once
#include <fstream>
#include <string>

class ToneLogger {
    std::ofstream logFile;
public:
    explicit ToneLogger(const std::string& filename);
    ~ToneLogger();
    void log(const std::string& message);
};
