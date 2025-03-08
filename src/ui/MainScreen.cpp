#include "MainScreen.h"

tone::ui::MainScreen::MainScreen(
    EditorScreen editor_screen,
    const MainInputProcessor &main_input_processor,
    std::shared_ptr<ToneLogger> toneLogger
): editor_screen(editor_screen),
   logger(toneLogger),
   main_input_processor(main_input_processor) {
    main_input_option = {
        .multiline = false,
        .on_enter = [&] {
            main_input_processor.process(main_input_value);
            main_input_value.clear();
        }
    };
    main_input = Input(&main_input_value, "Type your command here!", main_input_option);
    tab_toggle = ftxui::Toggle(&tab_values, &tab_selected);
    editor_container = ftxui::Container::Vertical({});
    devices_container = ftxui::Container::Vertical({});
    settings_container = ftxui::Container::Vertical({});
    tab_container = ftxui::Container::Tab(
        {
            editor_screen.render(),
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
    root_container = ftxui::Container::Vertical({
        main_input,
        tab_toggle,
        tab_container
    });
    renderer = Renderer(
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
}

ftxui::Component tone::ui::MainScreen::render() {
    logger->log("MainScreen render called");
    renderer = Renderer(
        root_container,
        [&] {
            logger->log("rendering was called");
            tab_container = ftxui::Container::Tab(
                {
                    editor_screen.render(),
                    Renderer(
                        devices_container,
                        [&] { return ftxui::text(std::to_string(std::time(nullptr))); }
                    ),
                    Renderer(
                        settings_container,
                        [&] { return ftxui::text("3"); }
                    )
                },
                &tab_selected
            );
            return vbox(
                main_input->Render(),
                ftxui::separator(),
                tab_toggle->Render(),
                ftxui::separator(),
                tab_container->Render()
            );
        });
    return renderer;
}

void tone::ui::MainScreen::start() {
}

void tone::ui::MainScreen::stop() {
}
