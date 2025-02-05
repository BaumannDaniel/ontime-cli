add_executable(
        tone_unit_tests
        InputTest.cpp
)
target_link_libraries(
        tone_unit_tests
        PRIVATE GTest::gtest_main
        PRIVATE tone_lib
)
gtest_discover_tests(tone_unit_tests)