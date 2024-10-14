#include <iostream>
#include <sstream>
#include <typeinfo>

#include "gbasictypes.hpp"

#pragma once

constexpr String boolToString(bool b) { return (b ? String{"true"} : String{"false"}); }

template <typename Type> constexpr bool isBoolType(const Type &toCheck) {
    return (typeid(toCheck) == typeid(bool));
}

template <typename Type> constexpr String typeToString(const Type &toConvert) {
    std::stringstream ss;
    ss << toConvert;
    return ss.str();
}

constexpr String typeToString(const bool &toConvert) { return boolToString(toConvert); }
