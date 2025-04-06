#include <string>

#include "input.h"

std::string tone::ui::trim_whitespace(std::string str) {
    const auto str_begin = str.find_first_not_of(WHITESPACE);
    if (str_begin == std::string::npos) return {};
    const auto str_end = str.find_last_not_of(WHITESPACE);

    str = str.substr(str_begin, str_end + 1 - str_begin);
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == WHITESPACE && str[i - 1] == WHITESPACE) str.erase(i, 1);
    }
    return str;
}

std::vector<std::string> tone::ui::parseInput(std::string input) {
    input = trim_whitespace(input);
    std::vector<std::string> segments = {};
    if (input.empty()) return segments;
    u_int32_t i = 0;
    u_int32_t y = 0;
    while (i < input.size()) {
        if (input.at(i) == WHITESPACE) {
            segments.insert(segments.end(), input.substr(y, i - y));
            i++;
            y = i;
            continue;
        }
        i++;
    }
    segments.insert(segments.end(), input.substr(y, i - y));
    return segments;
}
