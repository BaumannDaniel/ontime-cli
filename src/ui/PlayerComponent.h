#pragma once
#include <ftxui/component/component_base.hpp>

#include "Player.h"

namespace tone::ui {
    ftxui::Component create_player_component(
        std::shared_ptr<PlayerInfo> player_info
    );
}
