#include "EditorScreen.h"

#include <ftxui/component/component.hpp>
#include <utility>

#include "PlayerFragment.h"

tone::ui::EditorScreen::EditorScreen(
    DeviceFacade *device_facade,
    std::shared_ptr<ToneLogger> tone_logger
) : logger(std::move(tone_logger)),
    device_facade(device_facade) {
    root_container = ftxui::Container::Vertical({});
}

void tone::ui::EditorScreen::start() {
}

void tone::ui::EditorScreen::stop() {
}


ftxui::Component tone::ui::EditorScreen::render() {
    return Renderer(
        root_container,
        [&] {
            auto players_info = device_facade->get_players_info();
            ftxui::Elements players_fragments{};
            for (const auto &player_info: players_info) {
                players_fragments.push_back(PlayerFragment(player_info).render());
            }
            return vbox(players_fragments);
        }
    );
}
