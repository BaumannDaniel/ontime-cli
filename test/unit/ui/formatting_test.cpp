#include <gtest/gtest.h>

#include "formatting.h"

TEST(secondsToDisplayFormat, formatsSingleDigitSeconds) {
    const auto result = tone::ui::secondsToDisplayFormat(9, false);
    ASSERT_EQ("00:09", result);
}

TEST(secondsToDisplayFormat, formatsSingleDigitMinutes) {
    const auto result = tone::ui::secondsToDisplayFormat(72, false);
    ASSERT_EQ("01:12", result);
}

TEST(secondsToDisplayFormat, formatsSingleDigitHours) {
    const auto result = tone::ui::secondsToDisplayFormat(60 * 72, true);
    ASSERT_EQ("01:12:00", result);
}
