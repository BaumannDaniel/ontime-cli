#pragma once
#include <cstdint>
#include <vector>

#include "Player.h"

namespace tone {
    class DeviceFacade {
        std::vector<Player *> players{};

    public:
        uint64_t addPlayer(Player *player);
        void startPlayer(uint64_t playerId);
        void startAllPlayers();
        void pausePlayer(uint64_t playerId);
    };
}
