#include "ftxui/component/component.hpp"
#include "ftxui/component/screen_interactive.hpp"

#include "config.h" // NOLINT
#include "app_state_holder.h"
#include "device_id_manager.h"
#include "media_screen.h"
#include "ui/main_screen.h"

#ifdef BUILD_TYPE_DEBUG
constexpr bool is_debug_build = true;
#else
constexpr bool is_debug_build = false;
#endif

int main() {
    std::shared_ptr<tone::ILogger> logger = nullptr;
    if (is_debug_build) {
        auto log_file = "/home/daniel/Documents/tone_cli_workspace/log.txt";
        logger = std::make_shared<tone::DebugLogger>(log_file);
    } else {
        logger = std::make_shared<tone::ReleaseLogger>();
    }
    logger->log("----- Started Tone CLI -----");
    auto app_state_holder = std::make_shared<tone::AppStateHolder>();
    auto device_id_mapper = std::make_shared<tone::ui::DeviceIdManager>();
    auto device_repository = std::make_shared<tone::DeviceRepository>(tone::DeviceRepository());
    auto main_input_processor = std::make_shared<tone::ui::MainInputProcessor>(
        device_repository,
        device_id_mapper,
        app_state_holder,
        logger
    );
    auto editor_screen = createMediaScreen(device_repository, device_id_mapper, logger);
    auto main_screen = createMainScreen(editor_screen, main_input_processor, logger);
    auto screen = ftxui::ScreenInteractive::TerminalOutput();
    app_state_holder->observeExit().subscribe([&](std::monostate _) {
        screen.Exit();
    });
    std::thread update([&] {
        std::atomic run_thread = true;
        app_state_holder->observeExit().subscribe([&](std::monostate _) {
            run_thread = false;
        });
        while (run_thread) {
            sleep(1);
            screen.PostEvent(ftxui::Event::Custom);
        }
    });
    screen.Loop(main_screen);
    update.join();
}
