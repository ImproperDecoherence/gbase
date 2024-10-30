
#pragma once

#include "gzipper.hpp"
#include <iterator>
#include <ranges>

namespace gbase {

/**
 * @brief Mimics python's enumerate.
 *
 * @tparam Range Type of range (e.g. std::vector, std::set, std::ranges::range, std::ranges::view or
 * C-array).
 */
template <typename Range>
class GEnumerate : private GZipper<std::ranges::iota_view<Integer, Integer>, Range> {
    using base = GZipper<std::ranges::iota_view<Integer, Integer>, Range>;

  public:
    /**
     * @brief Construct a GEnumerate object.
     *
     * @param range The range to be enumerated.
     *
     * Example usage:
     * @code
     * const std::vector<Char> characters{'A', 'B', 'C'};
     *
     * for (const auto &[i, value] : GEnumerate(characters)) {
     *   ...

     * }
     *
     * const std::vector<Integer> integers{1, 2, 3, 4, 5, 6, 7, 8, 9};
     * auto add2 = std::ranges::views::transform([](Integer i) { return i + 2; });
     *
     * for (const auto &[i, value] : GEnumerate(integers | add2)) {
     *   ...
     * }
     * @endcode
     */
    GEnumerate(const Range &range)
        : base(std::ranges::views::iota(static_cast<Integer>(0),
                                        static_cast<Integer>(std::ranges::distance(range))),
               range) {}

    using base::begin;
    using base::end;
    using base::iterator;
    using base::Result;
};

} // namespace gbase