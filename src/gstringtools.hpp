#include <string>

#pragma once

template <typename... Args> constexpr String concatToString(Args &&...args) {
    std::ostringstream oss;
    (oss << ... << args); // Fold expression (C++17)
    return oss.str();
}

void constexpr eraseSubString(String &target, const String &subString) {
    const Size substringPos = target.find(subString);
    if (substringPos != String::npos) {
        target.erase(substringPos, subString.length());
    }
}