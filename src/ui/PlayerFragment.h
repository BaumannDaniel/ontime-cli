#pragma once
#include <ftxui/component/component_base.hpp>

#include "Player.h"

namespace tone::ui {
    class PlayerFragment {
        PlayerInfo player_info;
    public:
        PlayerFragment(PlayerInfo player_info);
        ftxui::Element render();
    };
}
