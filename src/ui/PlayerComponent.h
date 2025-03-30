#pragma once
#include <ftxui/component/component_base.hpp>

#include "domain/Player.h"

namespace tone::ui {
    ftxui::Component create_player_component(
        std::string ui_id,
        std::shared_ptr<PlayerInfo> player_info
    );
}
