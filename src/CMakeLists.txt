add_library(
        tone_lib
        Recorder.h
        DefaultRecorder.h DefaultRecorder.cpp
        Player.h
)
target_include_directories(tone_lib PRIVATE ${MINIAUDIO_INCLUDE_DIRS})
add_executable(tone_cli app.cpp)
target_include_directories(tone_cli PRIVATE ${MINIAUDIO_INCLUDE_DIRS})
target_link_libraries(tone_cli tone_lib)