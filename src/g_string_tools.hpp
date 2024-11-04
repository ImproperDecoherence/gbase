
#pragma once

#include <string>

namespace gbase {

/**
 * @brief Converts all given arguments to strings and concatenate them to one string.
 */
template <typename... Args> constexpr String concatToString(Args &&...args) {
    std::ostringstream oss;
    (oss << ... << args); // Fold expression (C++17)
    return oss.str();
}

/**
 * @brief Erases the subString from the target string.
 */
void constexpr eraseSubString(String &target, const String &subString) {
    const Size substringPos = target.find(subString);
    if (substringPos != String::npos) {
        target.erase(substringPos, subString.length());
    }
}

}