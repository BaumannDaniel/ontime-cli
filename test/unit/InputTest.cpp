#include <gtest/gtest.h>

#include "input.h"

TEST(trimWhitespace__removes_leading_whitespace, BasicAsserstions) {
    const std::string test_string = " test string";
    const auto trimmed_string = tone::ui::trimWhitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace__removes_trailing_whitespace, BasicAsserstions) {
    const std::string test_string = "test string ";
    const auto trimmed_string = tone::ui::trimWhitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}

TEST(trimWhitespace__removes_double_whitespace, BasicAsserstions) {
    const std::string test_string = "  test  string  ";
    const auto trimmed_string = tone::ui::trimWhitespace(test_string);
    ASSERT_EQ("test string", trimmed_string);
}