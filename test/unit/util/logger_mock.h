#pragma once
#include <gmock/gmock-function-mocker.h>

#include "logging.h"

namespace tone::test {
    class MockLogger : public ILogger {
    public:
        MOCK_METHOD(void, log, (const std::string &message), (override));
    };
}
