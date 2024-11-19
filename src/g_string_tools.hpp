
#pragma once

#include <algorithm>
#include <optional>
#include <ranges>
#include <string>

namespace gbase {

constexpr String underscoreToSpace(String in) {
    std::replace(in.begin(), in.end(), '_', ' ');
    return in;
}

constexpr String backslashToSlash(String in) {
    std::replace(in.begin(), in.end(), '\\', '/');
    return in;
}

template <typename T> std::ostream &operator<<(std::ostream &os, const std::optional<T> &opt) {
    if (opt.has_value()) {
        os << *opt;
    } else {
        os << "none";
    }
    return os;
}

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

} // namespace gbase