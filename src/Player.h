#pragma once

#include <string>
#include <boost/uuid/uuid.hpp>

#include "DeviceState.h"

namespace tone {
    class Player {
    public:
        DeviceState state = INIT;
        virtual ~Player() = default;
        virtual void play() = 0;
        virtual void pause() = 0;
        virtual void finish() = 0;
    };

    struct PlayerInfo {
        boost::uuids::uuid id;
        std::string file_name;
        uint64_t length;
        uint64_t position;
    };
}
