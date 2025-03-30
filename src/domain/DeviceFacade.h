#pragma once
#include <map>
#include <vector>

#include "Player.h"

namespace tone {
    class DeviceFacade {
        std::map<boost::uuids::uuid, std::shared_ptr<Player> > players{};

    public:
        void addPlayer(std::shared_ptr<Player> player);

        void removePlayer(boost::uuids::uuid player_id);

        void startPlayer(boost::uuids::uuid playerId) const;

        void stopPlayer(boost::uuids::uuid playerId) const;

        std::vector<std::shared_ptr<PlayerInfo> > get_players_info() const;
    };
}
