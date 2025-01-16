add_executable(ontime_cli app.cpp)
add_library(ontime_main DBusApi.h DefaultDBusApi.h DefaultDBusApi.cpp)
#target_link_libraries(ontime_main PRIVATE SDBusCpp::sdbus-c++)