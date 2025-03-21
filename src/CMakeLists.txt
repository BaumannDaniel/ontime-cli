add_library(
        tone_lib
        Recorder.h
        #DefaultRecorder.h DefaultRecorder.cpp
        Player.h Player.cpp
        DefaultPlayer.h DefaultPlayer.cpp
        DeviceState.h
        DeviceFacade.h DeviceFacade.cpp
        logging.h logging.cpp
        ui/Screen.h
        ui/MainScreen.h ui/MainScreen.cpp
        ui/EditorScreen.h ui/EditorScreen.cpp
        ui/PlayerComponent.h ui/PlayerComponent.cpp
        ui/MainInputProcessor.h ui/MainInputProcessor.cpp
        ui/input.h ui/input.cpp
)
target_link_libraries(
        tone_lib
        PRIVATE Boost::uuid
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