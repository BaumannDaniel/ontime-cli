add_library(
        tone_lib
        #DefaultRecorder.h DefaultRecorder.cpp
        domain/Player.h domain/Player.cpp
        domain/DeviceState.h
        domain/DeviceFacade.h domain/DeviceFacade.cpp
        domain/logging.h domain/logging.cpp
        ui/MainScreen.h ui/MainScreen.cpp
        ui/EditorScreen.h ui/EditorScreen.cpp
        ui/PlayerComponent.h ui/PlayerComponent.cpp
        ui/MainInputProcessor.h ui/MainInputProcessor.cpp
        ui/input.h ui/input.cpp
        ui/DeviceIdManager.h ui/DeviceIdManager.cpp
        ui/formatting.h ui/formatting.cpp
)
target_link_libraries(
        tone_lib
        PRIVATE Boost::uuid
        PRIVATE Boost::algorithm
)
target_include_directories(
        tone_lib
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}
        PUBLIC ${CMAKE_CURRENT_LIST_DIR}/ui
)
target_include_directories(tone_lib PRIVATE ${MINIAUDIO_INCLUDE_DIRS})
add_executable(tone_cli app.cpp)
target_include_directories(tone_cli PRIVATE ${MINIAUDIO_INCLUDE_DIRS})
target_link_libraries(
        tone_cli
        PRIVATE tone_lib
        PRIVATE ftxui::dom
        PRIVATE ftxui::screen
        PRIVATE ftxui::component
        PRIVATE rxcpp
)