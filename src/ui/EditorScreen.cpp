#include "EditorScreen.h"

#include <ftxui/component/component.hpp>

void tone::ui::EditorScreen::start() {
}

void tone::ui::EditorScreen::stop() {
}


ftxui::Component tone::ui::EditorScreen::render() {
    auto container = ftxui::Container::Vertical({});
    auto time = std::time(nullptr);
    return Renderer(
        container,
        [&] {
            return ftxui::hbox(
                ftxui::text(std::to_string(time)) | ftxui::border | ftxui::focus
            );
        }
    );
}
