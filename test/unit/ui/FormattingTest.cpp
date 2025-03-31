#include <gtest/gtest.h>

#include "formatting.h"

TEST(seconds_to_display_format, formats_single_digit_seconds) {
    const auto result = tone::ui::seconds_to_display_format(9, false);
    ASSERT_EQ("00:09", result);
}

TEST(seconds_to_display_format, formats_single_digit_minutes) {
    const auto result = tone::ui::seconds_to_display_format(72, false);
    ASSERT_EQ("01:12", result);
}

TEST(seconds_to_display_format, formats_single_digit_hours) {
    const auto result = tone::ui::seconds_to_display_format(60 * 72, true);
    ASSERT_EQ("01:12:00", result);
}
