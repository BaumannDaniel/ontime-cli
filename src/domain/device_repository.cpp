#include "device_repository.h"

#include <utility>

void tone::DeviceRepository::addPlayer(std::shared_ptr<IPlayer> player) {
    auto player_id = player->getPlayerInfo()->getId();
    player->init();
    players.insert(
        {
            player_id,
            std::move(player)
        });
}

void tone::DeviceRepository::removePlayer(boost::uuids::uuid player_id) {
    if (players.contains(player_id)) {
        players.at(player_id)->unInit();
        players.erase(player_id);
    }
}


void tone::DeviceRepository::startPlayer(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->start();
    }
}

void tone::DeviceRepository::stopPlayer(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->stop();
    }
}

void tone::DeviceRepository::changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const {
    if (players.contains(player_id)) {
        players.at(player_id)->changeFile(std::move(file_name));
    }
}


std::vector<std::shared_ptr<tone::IPlayerInfo> > tone::DeviceRepository::getPlayersInfo() const {
    auto players_info = std::vector<std::shared_ptr<IPlayerInfo> >{};
    for (const auto &player_pair: players) {
        players_info.push_back(player_pair.second->getPlayerInfo());
    }
    return players_info;
}
