#pragma once
#include <gmock/gmock-function-mocker.h>

#include "device_facade.h"

namespace tone::test {
    class MockDeviceFacade final : public IDeviceFacade {
    public:
        MOCK_METHOD(void, addPlayer, (std::shared_ptr<Player> player), (override));
        MOCK_METHOD(void, removePlayer, (boost::uuids::uuid player_id), (override));
        MOCK_METHOD(void, startPlayer, (boost::uuids::uuid player_id), (const, override));
        MOCK_METHOD(void, stopPlayer, (boost::uuids::uuid player_id), (const, override));
        MOCK_METHOD(void, changePlayerFile, (boost::uuids::uuid player_id, std::string file_name), (const, override));
        MOCK_METHOD(std::vector<std::shared_ptr<PlayerInfo> >, getPlayersInfo, (), (const, override));
    };
}
