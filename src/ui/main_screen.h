#pragma once
#include <ftxui/component/component_base.hpp>

#include "main_input_processor.h"

namespace tone::ui {
    struct MainScreenTabs {
        static constexpr std::string EDITOR = "Editor";
        static constexpr std::string SETTINGS = "Settings";
    };

    ftxui::Component createMainScreen(
        const ftxui::Component& editor_screen,
        const std::shared_ptr<MainInputProcessor>& main_input_processor,
        const std::shared_ptr<ILogger>& logger
    );
}
