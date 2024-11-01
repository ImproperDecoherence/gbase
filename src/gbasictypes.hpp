
#pragma once

#include <limits>
#include <ranges>
#include <stdexcept>
#include <string>
#include <type_traits>

namespace gbase {

using Unsigned = unsigned;
using Integer = int;
using Char = char;
using Byte = unsigned char;
using Size = size_t;
using String = std::string;

constexpr Integer integerMax = std::numeric_limits<int>::max();
constexpr Integer integerMin = std::numeric_limits<int>::min();

template <typename Range, typename Type>
concept RangeOf = std::ranges::range<Range> && std::same_as<std::ranges::range_value_t<Range>, Type>;

template <typename Range>
concept RangeOfRange = std::ranges::range<Range> && std::ranges::range<std::ranges::range_value_t<Range>>;

template <typename Range, typename Type>
concept IsRangeOfRangeOf =
    std::is_same_v<std::ranges::range_value_t<std::ranges::range_value_t<Range>>, Type>;

template <typename InputIt, typename Type>
concept InputIteratorOf = std::input_iterator<InputIt> && std::same_as<std::iter_value_t<InputIt>, Type>;

} // namespace gbase