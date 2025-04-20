#pragma once
#include <gmock/gmock-function-mocker.h>

#include "device_repository.h"

namespace tone::test {
    class MockDeviceRepository final : public IDeviceRepository {
    public:
        MOCK_METHOD(void, addPlayer, (std::shared_ptr<IPlayer> player), (override));
        MOCK_METHOD(void, addRecorder, (std::shared_ptr<IRecorder> recorder), (override));
        MOCK_METHOD(void, removeDevice, (boost::uuids::uuid player_id), (override));
        MOCK_METHOD(void, startDevice, (boost::uuids::uuid player_id), (const, override));
        MOCK_METHOD(void, stopDevice, (boost::uuids::uuid player_id), (const, override));
        MOCK_METHOD(void, changeDeviceFile, (boost::uuids::uuid player_id, std::string file_name), (const, override));
        MOCK_METHOD(std::vector<std::shared_ptr<IPlayerInfo> >, getPlayersInfo, (), (const, override));
        MOCK_METHOD(std::vector<std::shared_ptr<IRecorderInfo> >, getRecordersInfo, (), (const, override));
    };
}
