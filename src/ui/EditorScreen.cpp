#include "EditorScreen.h"

#include <ftxui/component/component.hpp>

#include "PlayerFragment.h"

tone::ui::EditorScreen::EditorScreen(
    DeviceFacade *device_facade,
    std::shared_ptr<ToneLogger> tone_logger
) : logger(tone_logger),
    device_facade(device_facade) {
}

void tone::ui::EditorScreen::start() {
}

void tone::ui::EditorScreen::stop() {
}


ftxui::Component tone::ui::EditorScreen::render() {
    auto container = ftxui::Container::Vertical({});
    return Renderer(
        container,
        [&] {
            auto players_info = device_facade->get_players_info();
            ftxui::Elements players_fragments{};
            for (const auto &player_info: players_info) {
                players_fragments.push_back(PlayerFragment(player_info).render());
            }
            return ftxui::vbox(players_fragments);
        }
    );
}
