add_library(
        tone_lib
        Recorder.h
        DefaultRecorder.h DefaultRecorder.cpp
        Player.h
        DefaultPlayer.h DefaultPlayer.cpp
        DeviceState.h
        ui/MainScreen.h ui/MainScreen.cpp
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
)