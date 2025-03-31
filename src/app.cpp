#define MINIAUDIO_IMPLEMENTATION

#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "DeviceIdManager.h"
#include "EditorScreen.h"
#include "ui/MainScreen.h"

int main() {
    auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
    auto logger = std::make_shared<ToneLogger>(log_file);
    logger->log("----- Started Tone CLI -----");
    auto device_id_mapper = std::make_shared<tone::ui::DeviceIdManager>();
    auto device_facade = std::make_shared<tone::DeviceFacade>(tone::DeviceFacade());
    auto main_input_processor = std::make_shared<tone::ui::MainInputProcessor>(device_facade, device_id_mapper, logger);
    auto editor_screen = create_editor_screen(device_facade, device_id_mapper, logger);
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
