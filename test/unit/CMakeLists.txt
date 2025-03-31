add_executable(
        tone_ui_unit_tests
        ui/InputTest.cpp
        ui/FormattingTest.cpp
)
target_link_libraries(
        tone_ui_unit_tests
        PRIVATE tone_ui_lib
        PRIVATE GTest::gtest_main
)
gtest_discover_tests(tone_ui_unit_tests)