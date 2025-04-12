add_executable(
        tone_ui_unit_tests
        ui/device_id_manager_test.cpp
        ui/formatting_test.cpp
        ui/input_test.cpp
        ui/main_input_processor_test.cpp
        domain/device_repository_test.cpp
        util/logger_mock.h
        util/device_repository_mock.h
        util/player_mock.h
)
target_link_libraries(
        tone_ui_unit_tests
        PRIVATE tone_ui_lib
        PRIVATE GTest::gtest_main
        PRIVATE GTest::gmock_main
)
gtest_discover_tests(tone_ui_unit_tests)