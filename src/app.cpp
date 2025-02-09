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
    std::string audioFile = "/home/daniel/Documents/tone_cli_workspace/test-track1.mp3";
    // auto recorder = DefaultRecorder(
    //     {
    //         .file = audioFile
    //     }
    // );
    // recorder.record();
    // printf("Press Enter to stop recording...\n");
    // getchar();
    // recorder.finish();
    auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
    auto logger = ToneLogger(log_file);
    auto player = DefaultPlayer(
        {
            .file = audioFile
        },
        &logger
    );
    player.play();
    logger.log("----- Started Tone CLI -----");
    auto main_input_processor = tone::ui::MainInputProcessor(&logger);
    auto main_screen = tone::ui::MainScreen(main_input_processor);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    screen.Loop(main_screen.render());
}
