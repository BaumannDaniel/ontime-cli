#pragma once
#include <map>
#include <vector>

#include "player.h"

namespace tone {
    class DeviceFacade {
        std::map<boost::uuids::uuid, std::shared_ptr<Player> > players{};

    public:
        void addPlayer(std::shared_ptr<Player> player);

        void removePlayer(boost::uuids::uuid player_id);

        void startPlayer(boost::uuids::uuid player_id) const;

        void stopPlayer(boost::uuids::uuid player_id) const;

        void changePlayerFile(boost::uuids::uuid player_id, std::string file_name) const;

        std::vector<std::shared_ptr<PlayerInfo> > getPlayersInfo() const;
    };
}
