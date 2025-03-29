#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>

#include "MainInputProcessor.h"

namespace tone::ui {
    struct MainScreenTabs {
        static constexpr std::string EDITOR = "Editor";
        static constexpr std::string SETTINGS = "Settings";
    };

    ftxui::Component create_main_screen(
        ftxui::Component editor_screen,
        std::shared_ptr<MainInputProcessor> main_input_processor,
        std::shared_ptr<ToneLogger> toneLogger
    );
}
