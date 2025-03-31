add_subdirectory(domain)
add_subdirectory(ui)

add_executable(tone_cli app.cpp)
target_link_libraries(
        tone_cli
        PRIVATE tone_ui_lib
        PRIVATE ftxui::dom
        PRIVATE ftxui::screen
        PRIVATE ftxui::component
)