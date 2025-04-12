#include "formatting.h"

#include <format>

std::string fill_time_value(u_int64_t time_value);

std::string tone::ui::secondsToDisplayFormat(const u_int64_t seconds, const bool use_hours) {
    const auto formatted_seconds = seconds % 60;
    const auto time_without_seconds = seconds - formatted_seconds;
    const auto minutes = time_without_seconds / 60;
    if (!use_hours) {
        return std::format("{}:{}", fill_time_value(minutes), fill_time_value(formatted_seconds));
    }
    const auto formatted_minutes = minutes % 60;
    const auto hours_in_minutes = minutes - formatted_minutes;
    const auto hours = hours_in_minutes / 60;
    return std::format(
        "{}:{}:{}",
        fill_time_value(hours),
        fill_time_value(formatted_minutes),
        fill_time_value(formatted_seconds)
    );
}

std::string fill_time_value(u_int64_t time_value) {
    if (time_value <= 9) {
        return std::format("0{}", time_value);
    }
    return std::to_string(time_value);
}
