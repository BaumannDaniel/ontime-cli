#include "MainScreen.h"

tone::ui::MainScreen::MainScreen(
    const MainInputProcessor &main_input_processor
): main_input_processor(main_input_processor) {
}

ftxui::Component tone::ui::MainScreen::render() {
    return renderer;
}

void tone::ui::MainScreen::start() {
}

void tone::ui::MainScreen::stop() {
}
