
#pragma once

#include <iostream>
#include <sstream>
#include <typeinfo>

#include "g_basic_types.hpp"

namespace gbase {

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

template <typename Type> String typeName(const Type &type) {
    std::stringstream ss;
    ss << typeid(decltype(type)).name() << std::endl;
    return ss.str();
}

#define CLASS_NAME() (typeid(*this).name())

} // namespace gbase