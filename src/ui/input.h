#pragma once
#include <string>
#include <vector>

namespace tone::ui {
    static constexpr char WHITESPACE = ' ';
    std::string trim_whitespace(std::string str);
    std::vector<std::string> parseInput(std::string input);
}
