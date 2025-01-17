add_executable(tone_cli app.cpp)
#add_library(ontime_main)
target_link_libraries(tone_cli PRIVATE portaudio_static)