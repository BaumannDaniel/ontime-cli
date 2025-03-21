#include "PlayerComponent.h"

#include <ftxui/component/component.hpp>

namespace tone::ui {
    class PlayerComponentBase : public ftxui::ComponentBase {
        std::shared_ptr<PlayerInfo> player_info;

    public:
        PlayerComponentBase(std::shared_ptr<PlayerInfo> player_info);

        ftxui::Element Render() override;
    };
}

tone::ui::PlayerComponentBase::PlayerComponentBase(
    std::shared_ptr<PlayerInfo> player_info
) : player_info(player_info) {
}

ftxui::Element tone::ui::PlayerComponentBase::Render() {
    return hbox(
        ftxui::text("id") | ftxui::border,
        ftxui::text(player_info->get_file_name()) | ftxui::border,
        ftxui::text(
            std::format(
                "{}:{}",
                std::to_string(player_info->get_file_position()),
                std::to_string(player_info->get_file_length()))
        ) | ftxui::border
    );
}

ftxui::Component tone::ui::create_player_component(std::shared_ptr<PlayerInfo> player_info) {
    return ftxui::Make<PlayerComponentBase>(player_info);
}

