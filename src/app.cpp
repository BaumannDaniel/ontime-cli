#include <cstdlib>
#include <iostream>

#define MINIAUDIO_IMPLEMENTATION
#include <miniaudio.h>
#include "ftxui/component/captured_mouse.hpp"  // for ftxui
#include "ftxui/component/component.hpp"       // for Toggle, Renderer, Vertical
#include "ftxui/component/component_base.hpp"  // for ComponentBase
#include "ftxui/component/screen_interactive.hpp"  // for Component, ScreenInteractive
#include "ftxui/dom/elements.hpp"  // for text, hbox, vbox, Element

#include "DefaultPlayer.h"
#include "DefaultRecorder.h"
#include "logging.h"
#include "ui/MainScreen.h"

int main() {
    auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
    auto logger = ToneLogger(log_file);
    logger.log("----- Started Tone CLI -----");
    auto device_facade = tone::DeviceFacade();
    auto main_input_processor = tone::ui::MainInputProcessor(&device_facade, &logger);
    auto main_screen = std::make_shared<tone::ui::MainScreen>(main_input_processor, &logger);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    std::thread update([&] {
        while (true) {
            sleep(1);
            screen.PostEvent(ftxui::Event::Custom);
        }
    });
    screen.Loop(main_screen->render());
}
