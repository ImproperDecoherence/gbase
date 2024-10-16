
#pragma once

#include <ostream>
#include <sstream>
#include <stdexcept>

#include "gbasictypes.hpp"
#include "gstringtools.hpp"

namespace gbase {

using GException = std::exception;
using GOutOfRange = std::out_of_range;
using GInvalidArgument = std::invalid_argument;

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

} // namespace gbase

constexpr std::ostream &operator<<(std::ostream &os, const gbase::GExceptionInfo &gei) {
    os << gei.type << '(' << gei.message << ')';
    return os;
};

constexpr std::ostream &operator<<(std::ostream &os, const gbase::GException &exception) {
    os << exception.what();
    return os;
};