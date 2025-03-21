#include <cstdlib>
#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include "ftxui/component/component.hpp"       // for Toggle, Renderer, Vertical
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive

#include "logging.h"
#include "ui/MainScreen.h"

int main() {
    auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
    auto logger = std::make_shared<ToneLogger>(log_file);
    logger->log("----- Started Tone CLI -----");
    auto device_facade = std::make_shared<tone::DeviceFacade>(tone::DeviceFacade());
    auto main_input_processor = std::make_shared<tone::ui::MainInputProcessor>(device_facade, logger);
    auto editor_screen = tone::ui::create_editor_screen(device_facade, logger);
    auto main_screen = create_main_screen(editor_screen, main_input_processor, logger);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    std::thread update([&] {
        while (true) {
            sleep(1);
            screen.PostEvent(ftxui::Event::Custom);
        }
    });
    screen.Loop(main_screen);
}
