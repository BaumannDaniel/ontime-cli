add_executable(tone_cli app.cpp)
target_include_directories(tone_cli PRIVATE ${MINIAUDIO_INCLUDE_DIRS})