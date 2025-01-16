add_executable(ontime_cli app.cpp)
add_library(ontime_main CalendarApi.h DefaultCalendarApi.h DefaultCalendarApi.cpp)
#target_link_libraries(ontime_main PRIVATE SDBusCpp::sdbus-c++)