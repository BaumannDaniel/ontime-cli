#include "MainScreen.h"

#include <utility>

tone::ui::MainScreen::MainScreen(
    EditorScreen editor_screen,
    const MainInputProcessor &main_input_processor,
    std::shared_ptr<ToneLogger> toneLogger
) : logger(std::move(toneLogger)),
    main_input_processor(main_input_processor),
    editor_screen(editor_screen) {
    main_input_option = {
        .multiline = false,
        .on_enter = [&] {
            main_input_processor.process(main_input_value);
            main_input_value.clear();
        }
    };
    main_input = Input(&main_input_value, "Type your command here!", main_input_option);
    tab_toggle = ftxui::Toggle(&tab_values, &tab_selected);
    settings_container = ftxui::Container::Vertical({});
    tab_container = ftxui::Container::Tab(
        {
            editor_screen.render(),
            Renderer(
                settings_container,
                [&] { return ftxui::text(std::to_string(std::time(nullptr))); }
            )
        },
        &tab_selected
    );
    root_container = ftxui::Container::Vertical({
        main_input,
        tab_toggle,
        tab_container
    });
}

ftxui::Component tone::ui::MainScreen::render() {
    return Renderer(
        root_container,
        [&] {
            logger->log("rendering was called");
            return vbox(
                main_input->Render(),
                ftxui::separator(),
                tab_toggle->Render(),
                ftxui::separator(),
                tab_container->Render()
            );
        });
}

void tone::ui::MainScreen::start() {
}

void tone::ui::MainScreen::stop() {
}
