
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
template <typename Range> class GEnumerate {
  public:
    using Type = std::ranges::range_value_t<Range>;
    using Iterator = std::ranges::iterator_t<Range>;

    struct Result {
        Integer index;
        Type value;
    };

    class iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = Result;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        constexpr iterator(Iterator start, Iterator end) : current_(start), end_(end) {}

        constexpr Result operator*() const { return Result{index_, *current_}; }

        constexpr iterator &operator++() {
            ++index_;
            ++current_;
            return *this;
        }

        constexpr iterator operator++(int) {
            iterator temp = *this;
            ++index_;
            ++current_;
            return temp;
        }

        constexpr bool operator!=(const iterator &other) const { return current_ != end_; }

      private:
        Integer index_;
        Iterator current_;
        Iterator end_;
    };

    /**
     * @brief Construct a GEnumerate object.
     *
     * @param range The range to enumerate.
     *
     * Example usage:
     *
     * @code
     * const std::vector<Char> characters{'A', 'B', 'C'};
     * for (const auto &[index, value] : GEnumerate(characters)) {
     *   ...
     * }
     *
     * const std::vector<Integer> integers{1, 2, 3, 4, 5, 6, 7, 8, 9};
     * auto add2 = std::ranges::views::transform([](Integer i) { return i + 2; });
     *
     * for (const auto &[index, value] : GEnumerate(integers | add2)) {
     *   ...
     * }
     *
     * auto large = std::ranges::views::filter([](Integer i) { return i > 4; });
     * for (const auto &[index, value] : GEnumerate(integers | large)) {
     *   ...
     * }
     * @endcode
     */
    GEnumerate(const Range &range) : range_{range} {}

    constexpr iterator begin() const {
        return iterator(std::ranges::begin(range_), std::ranges::end(range_));
    }

    constexpr iterator end() const { return iterator(std::ranges::end(range_), std::ranges::end(range_)); }

    constexpr iterator begin() { return iterator(std::ranges::begin(range_), std::ranges::end(range_)); }

    constexpr iterator end() { return iterator(std::ranges::end(range_), std::ranges::end(range_)); }

  private:
    Range range_;
};
// Deduction guide for GZipper
template <typename Range> GEnumerate(Range) -> GEnumerate<Range>;

} // namespace gbase