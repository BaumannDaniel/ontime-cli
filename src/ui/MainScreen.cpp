#include "MainScreen.h"

tone::ui::MainScreen::MainScreen(
    const MainInputProcessor &main_input_processor
): main_input_processor(main_input_processor) {
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
    return renderer;
}

void tone::ui::MainScreen::start() {
}

void tone::ui::MainScreen::stop() {
}
