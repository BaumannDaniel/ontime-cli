#include "PlayerFragment.h"

#include <ftxui/component/component.hpp>

tone::ui::PlayerFragment::PlayerFragment(PlayerInfo player_info) : player_info(player_info) {
}

ftxui::Element tone::ui::PlayerFragment::render() {
    return ftxui::hbox(
        ftxui::text("id")| ftxui::border,
        ftxui::text(player_info.get_file_name())| ftxui::border,
        ftxui::text(
            std::format(
                "{}:{}",
                std::to_string(player_info.get_file_position()),
                std::to_string(player_info.get_file_length()))
        )| ftxui::border
    );
}
