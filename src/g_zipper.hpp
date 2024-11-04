
#pragma once

#include <iterator>
#include <ranges>

#include "g_basic_types.hpp"
#include "g_exceptions.hpp"

namespace gbase {

/**
 * @brief Zips two ranges together.
 *
 * @tparam Range1 The first range type (e.g. std::vector, std::set, std::ranges::range, std::ranges::view or
 * C-array).
 * @tparam Range2 The second range type (e.g. std::vector, std::set, std::ranges::range, std::ranges::view or
 * C-array).
 */
template <typename Range1, typename Range2> class GZipper {
  public:
    using Type1 = std::ranges::range_value_t<Range1>;
    using Type2 = std::ranges::range_value_t<Range2>;
    using Iterator1 = std::ranges::iterator_t<Range1>;
    using Iterator2 = std::ranges::iterator_t<Range2>;

    struct Result {
        Type1 value1;
        Type2 value2;
    };

    class iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = Result;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        constexpr iterator(Iterator1 start1, Iterator2 start2, Iterator1 end1, Iterator2 end2)
            : current1_(start1), current2_(start2), end1_(end1), end2_(end2) {}

        constexpr Result operator*() const { return Result{*current1_, *current2_}; }

        constexpr iterator &operator++() {
            ++current1_;
            ++current2_;
            return *this;
        }

        constexpr iterator operator++(int) {
            iterator temp = *this;
            ++current1_;
            ++current2_;
            return temp;
        }

        constexpr bool operator!=(const iterator &other) const {
            return (current1_ != end1_) && (current2_ != end2_);
        }

      private:
        Iterator1 current1_;
        Iterator2 current2_;
        Iterator1 end1_;
        Iterator2 end2_;
    };

    /**
     * @brief Construct a GZipper object.
     *
     * @param range1 The first range.
     * @param range2 The scond range.
     *
     * Example usage:
     * @code
     * const std::vector<Char> characters{'A', 'B', 'C'};
     * const std::vector<Integer> integers{1, 2, 3};
     *
     * for (const auto &[c, i] : GZipper(characters, integers)) {
     *   ...
     * }
     *
     * auto add2 = std::ranges::views::transform([](Integer i) { return i + 2; });
     *
     *  for (const auto &[c, i] : GZipper(characters, integers | add2)) {
     *    ...
     * }
     * @endcode
     */
    GZipper(const Range1 &range1, const Range2 &range2) : range1_{range1}, range2_{range2} {
        const auto len1 = std::ranges::distance(range1_);
        const auto len2 = std::ranges::distance(range2_);

        if (len1 != len2) {
            GTHROW(GInvalidArgument, "Both ranges must be same length: ", len1, ", ", len2);
        }
    }

    constexpr iterator begin() const {
        return iterator(std::ranges::begin(range1_), std::ranges::begin(range2_), std::ranges::end(range1_),
                        std::ranges::end(range2_));
    }

    constexpr iterator end() const {
        return iterator(std::ranges::end(range1_), std::ranges::end(range2_), std::ranges::end(range1_),
                        std::ranges::end(range2_));
    }

    constexpr iterator begin() {
        return iterator(std::ranges::begin(range1_), std::ranges::begin(range2_), std::ranges::end(range1_),
                        std::ranges::end(range2_));
    }

    constexpr iterator end() {
        return iterator(std::ranges::end(range1_), std::ranges::end(range2_), std::ranges::end(range1_),
                        std::ranges::end(range2_));
    }

  private:
    Range1 range1_;
    Range2 range2_;
};

// Deduction guide for GZipper
template <typename Range1, typename Range2> GZipper(Range1, Range2) -> GZipper<Range1, Range2>;

} // namespace gbase