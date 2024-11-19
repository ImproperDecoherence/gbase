#pragma once

#include "g_basic_types.hpp"

namespace gbase {

constexpr Integer SecondsPerMinute = 60;
constexpr Integer MillisecondsPerSecond = 1000;
constexpr Integer MillisecondsPerMinute = SecondsPerMinute * MillisecondsPerSecond;

} // namespace gbase