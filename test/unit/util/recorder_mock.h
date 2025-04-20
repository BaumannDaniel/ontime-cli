#pragma once
#include <gmock/gmock-function-mocker.h>

#include "recorder_i.h"

namespace tone::test {
    class MockRecorder : public IRecorder {
    public:
        MOCK_METHOD(void, init, (), (override));
        MOCK_METHOD(void, start, (), (override));
        MOCK_METHOD(void, stop, (), (override));
        MOCK_METHOD(void, unInit, (), (override));
        MOCK_METHOD(std::shared_ptr<IRecorderInfo>, getRecorderInfo, (), (const, override));
    };
}
