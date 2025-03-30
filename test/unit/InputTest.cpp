#include <gtest/gtest.h>

#include "input.h"

TEST(trimWhitespace__removes_leading_whitespace, BasicAsserstions) {
    const std::string test_string = " test string";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace__removes_trailing_whitespace, BasicAsserstions) {
    const std::string test_string = "test string ";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace__removes_double_whitespace, BasicAsserstions) {
    const std::string test_string = "  test  string  ";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(parseInput__splits_input_string, BasicAsserstions) {
    const std::string test_string = "  test  string  ";
    const auto parsed_input = tone::ui::parse_input(test_string);
    ASSERT_EQ(2, parsed_input.size());
    ASSERT_EQ(parsed_input[0], "test");
    ASSERT_EQ(parsed_input[1], "string");
}

TEST(parseInput__handles_empty_string, BasicAsserstions) {
    const std::string test_string = "  ";
    const auto parsed_input = tone::ui::parse_input(test_string);
    ASSERT_EQ(0, parsed_input.size());
}