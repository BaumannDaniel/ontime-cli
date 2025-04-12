#pragma once
#include <gmock/gmock-function-mocker.h>

#include "logger_mock.h"
#include "player.h"

namespace tone::test {
    class MockPlayer : public Player {
    public:
        MockPlayer(): Player("", std::make_shared<MockLogger>()) {
        }

        MOCK_METHOD(void, init, (), (override));
        MOCK_METHOD(void, start, (), (override));
        MOCK_METHOD(void, stop, (), (override));
        MOCK_METHOD(void, unInit, (), (override));
        MOCK_METHOD(void, changeFile, (std::string file_name), (override));
        MOCK_METHOD(DeviceState, getDeviceState, (), (const, override));
        MOCK_METHOD(std::shared_ptr<PlayerInfo>, getPlayerInfo, (), (override));
    };
}
