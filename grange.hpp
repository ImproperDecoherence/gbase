#include <ranges>

#pragma once

template <typename Type> auto GRange(Type start, Type end) { return std::views::iota(start, end); }