#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>

#include "MainInputProcessor.h"
#include "Screen.h"

namespace tone::ui {
    struct MainScreenTabs {
        constexpr std::string EDITOR = "Editor";
        constexpr std::string DEVICES = "Devices";
        constexpr std::string SETTINGS = "Settings";
    };

    class MainScreen : Screen {
        MainInputProcessor main_input_processor;
        std::string main_input_value;
        ftxui::InputOption main_input_option;
        ftxui::Component main_input;
        int tab_selected = 0;
        const std::vector<std::string> tab_values{
            MainScreenTabs::EDITOR,
            MainScreenTabs::DEVICES,
            MainScreenTabs::SETTINGS,
        };
        ftxui::Component tab_toggle;
        ftxui::Component editor_container;
        ftxui::Component devices_container;
        ftxui::Component settings_container;
        ftxui::Component tab_container;
        ftxui::Component root_container;
        ftxui::Component renderer;

    public:
        explicit MainScreen(const MainInputProcessor &main_input_processor);

        void start() override;

        void stop() override;

        ftxui::Component render() override;
    };
}
