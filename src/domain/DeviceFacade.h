#pragma once
#include <map>
#include <vector>

#include "Player.h"

namespace tone {
    class DeviceFacade {
        std::map<boost::uuids::uuid, std::shared_ptr<Player> > players{};

    public:
        void add_player(std::shared_ptr<Player> player);

        void remove_player(boost::uuids::uuid player_id);

        void start_player(boost::uuids::uuid player_id) const;

        void stop_player(boost::uuids::uuid player_id) const;

        void change_player_file(boost::uuids::uuid player_id, std::string file_name) const;

        std::vector<std::shared_ptr<PlayerInfo> > get_players_info() const;
    };
}
