#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>

#include "DeviceState.h"

namespace tone {
    class PlayerInfo;

    class Player {
    protected:
        DeviceState state = INIT;

    public:
        virtual DeviceState getDeviceState();

        virtual ~Player() = default;

        virtual void play() = 0;

        virtual void pause() = 0;

        virtual void finish() = 0;

        virtual PlayerInfo get_player_info() = 0;
    };

    class PlayerInfo {
        boost::uuids::uuid id;
        std::string file_name;
        uint64_t file_length;
        uint64_t file_position;

        void set_file_name(std::string file_name);

        void set_file_length(uint64_t file_length);

        void set_file_position(uint64_t file_position);

    public:
        PlayerInfo(
            boost::uuids::uuid player_id,
            std::string file_name,
            uint64_t file_length,
            uint64_t file_position
        );

        boost::uuids::uuid get_id();

        std::string get_file_name();

        uint64_t get_file_length();

        uint64_t get_file_position();

        friend class Player;
    };
}
