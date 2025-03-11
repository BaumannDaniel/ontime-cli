#include "EditorScreen.h"

#include <ftxui/component/component.hpp>
#include <utility>

#include "PlayerFragment.h"


namespace tone::ui {
    class EditorScreenBase : public ftxui::ComponentBase {
        std::shared_ptr<ToneLogger> logger;
        std::shared_ptr<tone::DeviceFacade> device_facade;

    public:
        EditorScreenBase(std::shared_ptr<tone::DeviceFacade> device_facade, std::shared_ptr<ToneLogger> tone_logger);

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
    ftxui::Elements players_fragments{};
    for (const auto &player_info: players_info) {
        players_fragments.push_back(PlayerFragment(player_info).render());
    }
    return vbox(players_fragments);
}

ftxui::Component tone::ui::editor_screen(
    std::shared_ptr<DeviceFacade> device_facade,
    std::shared_ptr<ToneLogger> tone_logger
) {
    return ftxui::Make<EditorScreenBase>(device_facade, tone_logger);
}
