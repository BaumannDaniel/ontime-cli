#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>

#include "device_repository.h"
#include "recorder.h"
#include "../util/player_mock.h"
#include "../util/recorder_mock.h"

namespace tone::test {
    class DeviceRepositoryTest : public testing::Test {
    protected:
        const std::string test_file_1 = "/test/file1.mp3";
        const std::string test_file_2 = "/test/file2.mp3";
        std::shared_ptr<PlayerInfo> player_info_ptr = std::make_shared<PlayerInfo>(
            boost::uuids::random_generator()(),
            test_file_1,
            3,
            2,
            1
        );
        std::shared_ptr<RecorderInfo> recorder_info_ptr = std::make_shared<RecorderInfo>(
            boost::uuids::random_generator()(),
            test_file_1,
            2,
            1
        );
        std::shared_ptr<MockPlayer> mock_player_ptr = std::make_shared<MockPlayer>();
        std::shared_ptr<MockRecorder> mock_recorder_ptr = std::make_shared<MockRecorder>();
        DeviceRepository device_repository;
    };

    TEST_F(DeviceRepositoryTest, addPlayer$initalizesPlayer) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        EXPECT_CALL(
            *mock_player,
            init()
        ).Times(1);
        device_repository.addPlayer(mock_player_ptr);
    }

    TEST_F(DeviceRepositoryTest, addPlayer$addsPlayerToRepository) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        auto players_info = device_repository.getPlayersInfo();
        ASSERT_EQ(1, players_info.size());
        ASSERT_EQ(player_info_ptr.get(), players_info.front().get());
    }

    TEST_F(DeviceRepositoryTest, addRecorder$initalizesRecorder) {
        auto mock_recorder = mock_recorder_ptr.get();
        EXPECT_CALL(
            *mock_recorder,
            getRecorderInfo()
        ).WillRepeatedly(testing::Return(recorder_info_ptr));
        EXPECT_CALL(
            *mock_recorder,
            init()
        ).Times(1);
        device_repository.addRecorder(mock_recorder_ptr);
    }

    TEST_F(DeviceRepositoryTest, addRecorder$addsRecorderToRepository) {
        auto mock_recorder = mock_recorder_ptr.get();
        EXPECT_CALL(
            *mock_recorder,
            getRecorderInfo()
        ).WillRepeatedly(testing::Return(recorder_info_ptr));
        device_repository.addRecorder(mock_recorder_ptr);
        auto recorders_info = device_repository.getRecordersInfo();
        ASSERT_EQ(1, recorders_info.size());
        ASSERT_EQ(recorder_info_ptr.get(), recorders_info.front().get());
    }

    TEST_F(DeviceRepositoryTest, removeDevice$removesPlayerFromRepository) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        device_repository.removeDevice(player_info_ptr->getId());
        auto players_info = device_repository.getPlayersInfo();
        ASSERT_EQ(0, players_info.size());
    }

    TEST_F(DeviceRepositoryTest, removeDevice$removesRecorderFromRepository) {
        auto mock_recorder = mock_recorder_ptr.get();
        EXPECT_CALL(
            *mock_recorder,
            getRecorderInfo()
        ).WillRepeatedly(testing::Return(recorder_info_ptr));
        device_repository.addRecorder(mock_recorder_ptr);
        device_repository.removeDevice(recorder_info_ptr->getId());
        auto recorders_info = device_repository.getRecordersInfo();
        ASSERT_EQ(0, recorders_info.size());
    }

    TEST_F(DeviceRepositoryTest, startDevice$startsPlayer) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, start()).Times(1);
        device_repository.startDevice(player_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, startDevice$startsRecorder) {
        auto mock_recorder = mock_recorder_ptr.get();
        EXPECT_CALL(
            *mock_recorder,
            getRecorderInfo()
        ).WillRepeatedly(testing::Return(recorder_info_ptr));
        device_repository.addRecorder(mock_recorder_ptr);
        EXPECT_CALL(*mock_recorder, start()).Times(1);
        device_repository.startDevice(recorder_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, stopDevice$stopsPlayer) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, stop()).Times(1);
        device_repository.stopDevice(player_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, stopDevice$stopsRecorder) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, stop()).Times(1);
        device_repository.stopDevice(player_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, changeDeviceFile$changesPlayerFile) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, changeFile(test_file_2)).Times(1);
        device_repository.changeDeviceFile(player_info_ptr->getId(), test_file_2);
    }
}
