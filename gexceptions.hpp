#include <ostream>
#include <sstream>
#include <stdexcept>

#include "gbasictypes.hpp"
#include "gstringtools.hpp"

#pragma once

typedef std::exception GException;
typedef std::out_of_range GOutOfRange;
typedef std::invalid_argument GInvalidArgument;

#define GTHROW(exc, ...)                                                                                     \
    do {                                                                                                     \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | line: " << __LINE__ << " | ";                            \
        oss << concatToString(__VA_ARGS__);                                                                  \
        throw exc(oss.str());                                                                                \
    } while (false);

struct GExceptionInfo {
    explicit GExceptionInfo(const GException &e) : message{e.what()}, type{typeid(e).name()} {}

    String message;
    String type;
};

constexpr std::ostream &operator<<(std::ostream &os, const GExceptionInfo &gei) {
    os << gei.type << '(' << gei.message << ')';
    return os;
};

constexpr std::ostream &operator<<(std::ostream &os, const GException &exception) {
    os << exception.what();
    return os;
};