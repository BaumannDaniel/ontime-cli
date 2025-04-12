#include "device_repository.h"

#include <boost/uuid/random_generator.hpp>
#include <gtest/gtest.h>

#include "../util/player_mock.h"

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
        std::shared_ptr<MockPlayer> mock_player_ptr = std::make_shared<MockPlayer>();
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

    TEST_F(DeviceRepositoryTest, removePlayer$removesPlayerFromRepository) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        device_repository.removePlayer(player_info_ptr->getId());
        auto players_info = device_repository.getPlayersInfo();
        ASSERT_EQ(0, players_info.size());
    }

    TEST_F(DeviceRepositoryTest, startPlayer$startsPlayer) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, start()).Times(1);
        device_repository.startPlayer(player_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, stopPlayer$stopsPlayer) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, stop()).Times(1);
        device_repository.stopPlayer(player_info_ptr->getId());
    }

    TEST_F(DeviceRepositoryTest, changePlayerFile$changesFile) {
        auto mock_player = mock_player_ptr.get();
        EXPECT_CALL(
            *mock_player,
            getPlayerInfo()
        ).WillRepeatedly(testing::Return(player_info_ptr));
        device_repository.addPlayer(mock_player_ptr);
        EXPECT_CALL(*mock_player, changeFile(test_file_2)).Times(1);
        device_repository.changePlayerFile(player_info_ptr->getId(), test_file_2);
    }
}
