#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "config.h" // NOLINT
#include "device_id_manager.h"
#include "editor_screen.h"
#include "ui/main_screen.h"

int main() {
    auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
    auto logger = std::make_shared<tone::DebugLogger>(log_file);
    logger->log("----- Started Tone CLI -----");
    auto device_id_mapper = std::make_shared<tone::ui::DeviceIdManager>();
    auto device_repository = std::make_shared<tone::DeviceRepository>(tone::DeviceRepository());
    auto main_input_processor = std::make_shared<tone::ui::MainInputProcessor>(device_repository, device_id_mapper, logger);
    auto editor_screen = createEditorScreen(device_repository, device_id_mapper, logger);
    auto main_screen = createMainScreen(editor_screen, main_input_processor, logger);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    std::thread update([&] {
        while (true) {
            sleep(1);
            screen.PostEvent(ftxui::Event::Custom);
        }
    });
    screen.Loop(main_screen);
}
