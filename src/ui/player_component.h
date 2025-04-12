#pragma once
#include <ftxui/component/component_base.hpp>

#include "player.h"

namespace tone::ui {
    ftxui::Component createPlayerComponent(
        const std::string& ui_id,
        const std::shared_ptr<PlayerInfo>& player_info
    );
}
