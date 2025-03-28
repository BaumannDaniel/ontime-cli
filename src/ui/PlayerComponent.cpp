#include "PlayerComponent.h"

#include <ftxui/component/component.hpp>
#include <utility>

namespace tone::ui {
    class PlayerComponentBase : public ftxui::ComponentBase {
        std::string ui_id;
        std::shared_ptr<PlayerInfo> player_info;

    public:
        PlayerComponentBase(
            std::string ui_id,
            std::shared_ptr<PlayerInfo> player_info
        );

        ftxui::Element Render() override;
    };
}

tone::ui::PlayerComponentBase::PlayerComponentBase(
    std::string ui_id,
    std::shared_ptr<PlayerInfo> player_info
) : ui_id(std::move(ui_id)),
    player_info(std::move(player_info)) {
}

ftxui::Element tone::ui::PlayerComponentBase::Render() {
    auto player_sample_rate = player_info->get_sample_rate();
    auto file_length_seconds = player_info->get_number_of_pcm_frames() / player_sample_rate;
    auto current_file_position = player_info->get_current_pcm_frame_number() / player_sample_rate;
    return hbox(
        ftxui::text(std::format("Player {}", ui_id)) | ftxui::border,
        ftxui::text(player_info->get_file_name()) | ftxui::border,
        ftxui::text(
            std::format(
                "{}:{}",
                std::to_string(current_file_position),
                std::to_string(file_length_seconds)
            )
        ) | ftxui::border
    );
}

ftxui::Component tone::ui::create_player_component(
    std::string ui_id,
    std::shared_ptr<PlayerInfo> player_info
) {
    return ftxui::Make<PlayerComponentBase>(ui_id, player_info);
}
