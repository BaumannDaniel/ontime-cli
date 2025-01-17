add_executable(
        ontime_test
        DBusCalendarApiTest.cpp
)
target_link_libraries(ontime_test PRIVATE GTest::gtest_main)
gtest_discover_tests(ontime_test)