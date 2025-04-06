#pragma once
#include <ftxui/component/component_base.hpp>

#include "player.h"

namespace tone::ui {
    ftxui::Component createPlayerComponent(
        std::string ui_id,
        std::shared_ptr<PlayerInfo> player_info
    );
}
