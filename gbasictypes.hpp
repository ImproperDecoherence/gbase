
#include <limits>
#include <ranges>
#include <stdexcept>
#include <string>
#include <type_traits>

#pragma once

typedef unsigned Unsigned;
typedef int Integer;
typedef char Char;
typedef unsigned char Byte;
typedef size_t Size;
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
