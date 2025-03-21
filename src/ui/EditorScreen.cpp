#include "EditorScreen.h"

#include <map>
#include <ftxui/component/component.hpp>
#include <utility>

#include "PlayerComponent.h"


namespace tone::ui {
    class EditorScreenBase : public ftxui::ComponentBase {
        std::shared_ptr<ToneLogger> logger;
        std::shared_ptr<DeviceFacade> device_facade;
        std::map<boost::uuids::uuid, ftxui::Component> player_components;

    public:
        EditorScreenBase(std::shared_ptr<DeviceFacade> device_facade, std::shared_ptr<ToneLogger> tone_logger);

        ftxui::Element Render() override;
    };
}

tone::ui::EditorScreenBase::EditorScreenBase(
    std::shared_ptr<DeviceFacade> device_facade,
    std::shared_ptr<ToneLogger> tone_logger
) : logger(std::move(tone_logger)),
    device_facade(std::move(device_facade)) {
}

ftxui::Element tone::ui::EditorScreenBase::Render() {
    auto players_info = device_facade->get_players_info();
    for (const auto &player_info: players_info) {
        auto player_id = player_info->get_id();
        if (player_components.contains(player_id)) continue;
        auto player_component = create_player_component(player_info);
        player_components.insert({player_id, player_component});
    }
    std::vector<ftxui::Element> player_elements;
    for (auto player : player_components) {
        player_elements.push_back(player.second->Render());
    }
    return ftxui::vbox(player_elements);
}

ftxui::Component tone::ui::create_editor_screen(
    std::shared_ptr<DeviceFacade> device_facade,
    std::shared_ptr<ToneLogger> tone_logger
) {
    return ftxui::Make<EditorScreenBase>(device_facade, tone_logger);
}
