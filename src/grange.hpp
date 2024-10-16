
#pragma once

#include <ranges>

namespace gbase {

template <typename Type> auto GRange(Type start, Type end) { return std::views::iota(start, end); }

} // namespace gbase