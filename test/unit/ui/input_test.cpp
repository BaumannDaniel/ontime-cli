#include <gtest/gtest.h>

#include "input.h"

TEST(trimWhitespace, removesLeadingWhitespace) {
    const std::string test_string = " test string";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace, removesTrailingWhitespace) {
    const std::string test_string = "test string ";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace, removesDoubleWhitespace) {
    const std::string test_string = "  test  string  ";
    const auto trimmed_string = tone::ui::trim_whitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(parseInput, splitsInputString) {
    const std::string test_string = "  test  string  ";
    const auto parsed_input = tone::ui::parseInput(test_string);
    ASSERT_EQ(2, parsed_input.size());
    ASSERT_EQ(parsed_input[0], "test");
    ASSERT_EQ(parsed_input[1], "string");
}

TEST(parseInput, handlesEmptyString) {
    const std::string test_string = "  ";
    const auto parsed_input = tone::ui::parseInput(test_string);
    ASSERT_EQ(0, parsed_input.size());
}