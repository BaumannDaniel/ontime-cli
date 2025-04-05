#include "device_facade.h"

#include <utility>

void tone::device_facade::add_player(std::shared_ptr<player> player) {
    auto player_id = player->get_player_info()->get_id();
    player->init();
    players.insert(
        {
            player_id,
            std::move(player)
        });
}

void tone::device_facade::remove_player(boost::uuids::uuid player_id) {
    if (players.contains(player_id)) {
        players.at(player_id)->un_init();
        players.erase(player_id);
    }
}


void tone::device_facade::start_player(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->start();
    }
}

void tone::device_facade::stop_player(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->stop();
    }
}

void tone::device_facade::change_player_file(boost::uuids::uuid player_id, std::string file_name) const {
    if (players.contains(player_id)) {
        players.at(player_id)->change_file(std::move(file_name));
    }
}


std::vector<std::shared_ptr<tone::PlayerInfo> > tone::device_facade::get_players_info() const {
    auto players_info = std::vector<std::shared_ptr<PlayerInfo> >{};
    for (const auto &player_pair: players) {
        players_info.push_back(player_pair.second->get_player_info());
    }
    return players_info;
}
