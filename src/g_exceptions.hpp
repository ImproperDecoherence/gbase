
#pragma once

#include <ostream>
#include <sstream>
#include <stdexcept>

#include "g_basic_types.hpp"
#include "g_string_tools.hpp"

namespace gbase {

using GException = std::exception;
using GOutOfRange = std::out_of_range;
using GInvalidArgument = std::invalid_argument;

/**
 * @def GTHROW(exc, ...)
 * @brief Throws an exception of type 'exc' and captures the filename, the line number and the name of the
 * function in the message of the exception.
 *
 * Example usage:
 * @code
 * GTHROW(GInvalidArgument, "Value must be less than 3: ", value);
 * @endcode
 */
#define GTHROW(exc, ...)                                                                                     \
    {                                                                                                        \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | line: " << __LINE__ << " | ";                            \
        oss << concatToString(__VA_ARGS__);                                                                  \
        throw exc(oss.str());                                                                                \
    }

/**
 * @brief Captures the message and name of given exception.
 */
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