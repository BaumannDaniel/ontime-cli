add_library(
        tone_ui_lib
        MainScreen.h MainScreen.cpp
        EditorScreen.h EditorScreen.cpp
        PlayerComponent.h PlayerComponent.cpp
        MainInputProcessor.h MainInputProcessor.cpp
        input.h input.cpp
        DeviceIdManager.h DeviceIdManager.cpp
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