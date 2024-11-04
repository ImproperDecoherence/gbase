#pragma once

#include "g_basic_types.hpp"
#include <functional>
#include <ranges>

namespace gbase {

template <typename Type>
using GRangeType = std::ranges::transform_view<std::ranges::iota_view<int>, std::function<Type(int)>>;

template <typename Type> using GRangeIterator = std::ranges::iterator_t<GRangeType<Type>>;

template <typename Type> constexpr Type limit(Type value, Type lowerLimit, Type upperLimit) {
    return std::max(std::min(value, upperLimit), lowerLimit);
}

template <typename Type, typename Func>
constexpr auto genericRange(Type begin, Type end, gbase::Integer numberOfSteps, Func func) {
    return std::ranges::views::iota(0, numberOfSteps) | std::ranges::views::transform([=](int i) {
               return func(begin + (end - begin) / numberOfSteps * i);
           });
}

template <typename Type, typename Func>
constexpr auto genericRange(Type begin, Type end, Type stepSize, Func func) {
    if ((begin < end) && (stepSize < 0)) {
        stepSize = -stepSize;
    }
    return std::ranges::views::iota(0, static_cast<int>((end - begin) / stepSize) + 1) |
           std::ranges::views::transform([=](int i) { return func(begin + stepSize * i); });
}

template <typename Type> constexpr auto linearRange(Type begin, Type end, gbase::Integer numberOfSteps) {
    return genericRange(begin, end, numberOfSteps, [](Type value) { return value; });
}

template <typename Type> constexpr auto linearRange(Type begin, Type end, Type stepSize) {
    return genericRange(begin, end, stepSize, [](Type value) { return value; });
}

} // namespace gbase
