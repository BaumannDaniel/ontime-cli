#include "device_repository.h"

#include <utility>

void tone::DeviceRepository::addPlayer(std::shared_ptr<IPlayer> player) {
    auto player_id = player->getPlayerInfo()->getId();
    player->init();
    std::unique_lock lock(device_repository_mutex);
    players.insert(
        {
            player_id,
            std::move(player)
        });
}

void tone::DeviceRepository::addRecorder(std::shared_ptr<IRecorder> recorder) {
    auto player_id = recorder->getRecorderInfo()->getId();
    recorder->init();
    std::unique_lock lock(device_repository_mutex);
    recorders.insert(
        {
            player_id,
            std::move(recorder)
        });
}

void tone::DeviceRepository::removeDevice(boost::uuids::uuid device_id) {
    std::unique_lock lock(device_repository_mutex);
    if (players.contains(device_id)) {
        players.at(device_id)->unInit();
        players.erase(device_id);
        return;
    }
    if (recorders.contains(device_id)) {
        recorders.at(device_id)->unInit();
        recorders.erase(device_id);
    }
}


void tone::DeviceRepository::startDevice(boost::uuids::uuid device_id) const {
    std::shared_lock lock(device_repository_mutex);
    if (players.contains(device_id)) {
        players.at(device_id)->start();
        return;
    }
    if (recorders.contains(device_id)) {
        recorders.at(device_id)->start();
    }
}

void tone::DeviceRepository::stopDevice(boost::uuids::uuid device_id) const {
    std::shared_lock lock(device_repository_mutex);
    if (players.contains(device_id)) {
        players.at(device_id)->stop();
        return;
    }
    if (recorders.contains(device_id)) {
        recorders.at(device_id)->stop();
    }
}

void tone::DeviceRepository::changeDeviceFile(boost::uuids::uuid device_id, std::string file_name) const {
    std::shared_lock lock(device_repository_mutex);
    if (players.contains(device_id)) {
        players.at(device_id)->changeFile(std::move(file_name));
        return;
    }
    if (recorders.contains(device_id)) {
    }
}


std::vector<std::shared_ptr<tone::IPlayerInfo> > tone::DeviceRepository::getPlayersInfo() const {
    std::shared_lock lock(device_repository_mutex);
    auto players_info = std::vector<std::shared_ptr<IPlayerInfo> >{};
    for (const auto &player_pair: players) {
        players_info.push_back(player_pair.second->getPlayerInfo());
    }
    return players_info;
}

std::vector<std::shared_ptr<tone::IRecorderInfo> > tone::DeviceRepository::getRecordersInfo() const {
    std::shared_lock lock(device_repository_mutex);
    auto recorders_info = std::vector<std::shared_ptr<IRecorderInfo>>{};
    for (const auto &recorder_pair: recorders) {
        recorders_info.push_back(recorder_pair.second->getRecorderInfo());
    }
    return recorders_info;
}

