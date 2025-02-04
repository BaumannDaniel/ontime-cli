#include <string>

#include "input.h"

std::string tone::ui::trimWhitespace(std::string str) {
    const auto str_begin = str.find_first_not_of(WHITESPACE);
    if (str_begin == std::string::npos) return {};
    const auto str_end = str.find_last_not_of(WHITESPACE);

    str = str.substr(str_begin, str_end - str_begin);
    for (int i = 1; i < str.size(); i++) {
        if (str[i] == WHITESPACE && str[i - 1] == WHITESPACE) str.erase(i);
    }
    return str;
}

