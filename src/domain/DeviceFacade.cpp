#include "DeviceFacade.h"

void tone::DeviceFacade::add_player(std::shared_ptr<Player> player) {
    auto player_id = player->get_player_info()->get_id();
    player->init();
    players.insert(
        {
            player_id,
            std::move(player)
        });
}

void tone::DeviceFacade::remove_player(boost::uuids::uuid player_id) {
    if (players.contains(player_id)) {
        players.at(player_id)->un_init();
        players.erase(player_id);
    }
}


void tone::DeviceFacade::start_player(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->start();
    }
}

void tone::DeviceFacade::stop_player(boost::uuids::uuid playerId) const {
    if (players.contains(playerId)) {
        players.at(playerId)->stop();
    }
}

std::vector<std::shared_ptr<tone::PlayerInfo> > tone::DeviceFacade::get_players_info() const {
    auto players_info = std::vector<std::shared_ptr<PlayerInfo> >{};
    for (const auto &player_pair: players) {
        players_info.push_back(player_pair.second->get_player_info());
    }
    return players_info;
}
