#include <ftxui/component/component.hpp>
#include <utility>
#include <boost/algorithm/string.hpp>

#include "PlayerComponent.h"
#include "formatting.h"


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
    auto formatted_player_id = std::format("Player {} ", boost::to_upper_copy(ui_id));
    auto formatted_player_file_name = std::format(" {} ", player_info->get_file_name());
    auto player_sample_rate = player_info->get_sample_rate();
    auto file_length_seconds = player_info->get_number_of_pcm_frames() / player_sample_rate;
    auto current_file_position = player_info->get_current_pcm_frame_number() / player_sample_rate;
    auto show_hours = file_length_seconds >= 60 * 60;
    auto formatted_position = seconds_to_display_format(current_file_position, show_hours);
    auto formatted_length = seconds_to_display_format(file_length_seconds, show_hours);
    auto formatted_progress = std::format(" {} / {}", formatted_position, formatted_length);
    return vbox(
               hbox(
                   ftxui::text(formatted_player_id),
                   ftxui::separator(),
                   ftxui::text(formatted_player_file_name),
                   ftxui::separator(),
                   ftxui::text(formatted_progress)
               )
           ) | ftxui::border;
}

ftxui::Component tone::ui::create_player_component(
    std::string ui_id,
    std::shared_ptr<PlayerInfo> player_info
) {
    return ftxui::Make<PlayerComponentBase>(ui_id, player_info);
}
