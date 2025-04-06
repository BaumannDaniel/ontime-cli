#pragma once
#include <fstream>
#include <mutex>
#include <string>

namespace tone {
    class ILogger {
    public:
        virtual ~ILogger() = default;

        virtual void log(const std::string &message) = 0;
    };

    class DebugLogger : public ILogger {
        std::mutex log_mutex_;
        std::ofstream log_file_;

    public:
        explicit DebugLogger(const std::string &filename);

        ~DebugLogger() override;

        void log(const std::string &message) override;
    };

    class ReleaseLogger : public ILogger {
    public:
        void log(const std::string &message) override;
    };
}
