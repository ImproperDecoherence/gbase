
#pragma once

#include "gbasictypes.hpp"
#include <iterator>
#include <ranges>

namespace gbase {

template <typename Range> class GEnumerate {
  public:
    using Type = std::ranges::range_value_t<Range>;

    struct Result {
        Size index;
        Type value;
    };

    class iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = Result;
        using pointer = const value_type *;
        using reference = const value_type &;
        using iterator_category = std::input_iterator_tag;

        constexpr explicit iterator(typename Range::const_iterator start) : current_(start) {}

        constexpr Result operator*() { return Result{index_, *current_}; }

        constexpr iterator &operator++() {
            ++current_;
            ++index_;
            return *this;
        }

        constexpr iterator operator++(int) {
            iterator temp = *this;
            ++current_;
            ++index_;
            return temp;
        }

        constexpr bool operator!=(const iterator &other) const { return current_ != other.current_; }

      private:
        typename Range::const_iterator current_;
        Size index_{0};
    };

    GEnumerate(const Range &range) : range_{range} {}

    iterator begin() const { return iterator{range_.begin()}; }

    iterator end() const { return iterator{range_.end()}; }

  private:
    const Range &range_;
};

} // namespace gbase