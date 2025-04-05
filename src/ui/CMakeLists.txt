add_library(
        tone_ui_lib
        main_screen.h main_screen.cpp
        editor_screen.h editor_screen.cpp
        player_component.h player_component.cpp
        main_input_processor.h main_input_processor.cpp
        input.h input.cpp
        device_id_manager.h device_id_manager.cpp
        formatting.h formatting.cpp
)

target_include_directories(
        tone_ui_lib
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
)

target_link_libraries(
        tone_ui_lib
        PUBLIC tone_domain_lib
        PRIVATE Boost::uuid
        PRIVATE Boost::algorithm
        PRIVATE ftxui::dom
        PRIVATE ftxui::screen
        PRIVATE ftxui::component
)