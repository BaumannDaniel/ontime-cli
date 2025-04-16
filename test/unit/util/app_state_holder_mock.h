#pragma once
#include <gmock/gmock-function-mocker.h>

#include "app_state_holder.h"

namespace tone::test {
    class MockAppStateHolder : public IAppStateHolder {
    public:
        MOCK_METHOD(rxcpp::observable<std::monostate>, observeExit, (), (override));
        MOCK_METHOD(void, exit, (), (override));
    };
}
