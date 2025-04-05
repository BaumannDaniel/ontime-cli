#pragma once
#include <map>
#include <vector>

#include "player.h"

namespace tone {
    class device_facade {
        std::map<boost::uuids::uuid, std::shared_ptr<player> > players{};

    public:
        void add_player(std::shared_ptr<player> player);

        void remove_player(boost::uuids::uuid player_id);

        void start_player(boost::uuids::uuid player_id) const;

        void stop_player(boost::uuids::uuid player_id) const;

        void change_player_file(boost::uuids::uuid player_id, std::string file_name) const;

        std::vector<std::shared_ptr<PlayerInfo> > get_players_info() const;
    };
}
