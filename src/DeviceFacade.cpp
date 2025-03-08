#include "DeviceFacade.h"

uint64_t tone::DeviceFacade::addPlayer(Player* player) {
    players.insert(players.end(), player);
    return players.size();
}

void tone::DeviceFacade::startPlayer(uint64_t playerId) {
    if (players.size() <= playerId) {
        players[playerId - 1]->play();
    }
}


void tone::DeviceFacade::startAllPlayers() {
    for (const auto player : players) {
        player->play();
    }
}

void tone::DeviceFacade::pausePlayer(uint64_t playerId) {
    if (players.size() <= playerId) {
        players[playerId - 1]->pause();
    }
}

std::vector<tone::PlayerInfo> tone::DeviceFacade::get_players_info() {
    auto players_info = std::vector<PlayerInfo>{};
    for (const auto player : players) {
        players_info.push_back(player->get_player_info());
    }
    return players_info;
}
