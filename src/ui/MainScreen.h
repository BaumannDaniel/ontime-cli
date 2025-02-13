#pragma once
#include <ftxui/component/component.hpp>
#include <ftxui/component/component_base.hpp>
#include <ftxui/component/component_options.hpp>

#include "MainInputProcessor.h"
#include "Screen.h"

namespace tone::ui {
    class MainScreen : Screen {
        MainInputProcessor main_input_processor;
        std::string main_input_value;
        ftxui::InputOption main_input_option = {
            .multiline = false,
            .on_enter = [&] {
                main_input_processor.process(main_input_value);
                main_input_value.clear();
            }
        };
        ftxui::Component main_input = Input(&main_input_value, "Type your command here!", main_input_option);
        int tab_selected = 0;
        std::vector<std::string> tab_values{
            "Editor",
            "Devices",
            "Settings",
        };
        ftxui::Component tab_toggle = ftxui::Toggle(&tab_values, &tab_selected);
        ftxui::Component editor_container = ftxui::Container::Vertical({});
        ftxui::Component devices_container = ftxui::Container::Vertical({});
        ftxui::Component settings_container = ftxui::Container::Vertical({});
        ftxui::Component tab_container = ftxui::Container::Tab(
            {
                Renderer(
                    editor_container,
                    [&] { return ftxui::text("1"); }
                ),
                Renderer(
                    devices_container,
                    [&] { return ftxui::text("2"); }
                ),
                Renderer(
                    settings_container,
                    [&] { return ftxui::text("3"); }
                )
            },
            &tab_selected
        );

        // The component tree:
        ftxui::Component root_container = ftxui::Container::Vertical({
            main_input,
            tab_toggle,
            tab_container
        });

        // Tweak how the component tree is rendered:
        ftxui::Component renderer = Renderer(
            root_container,
            [&] {
                return vbox(
                    main_input->Render(),
                    ftxui::separator(),
                    tab_toggle->Render(),
                    ftxui::separator(),
                    tab_container->Render()
                );
            });

    public:
        explicit MainScreen(const MainInputProcessor &main_input_processor);

        void start() override;
        void stop() override;
        ftxui::Component render() override;
    };
}
