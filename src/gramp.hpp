#pragma once

#include <cmath>
#include <functional>

#include "gbasictypes.hpp"

namespace gbase {

template <typename Type> class GRamp {

  public:
    using Function = std::function<Type(Type)>;

    class iterator {
      public:
        using difference_type = std::ptrdiff_t;
        using value_type = Type;
        using pointer = value_type *;
        using reference = value_type &;
        using iterator_category = std::input_iterator_tag;

        constexpr iterator(Function func, Integer steps, Type base, Type scale, Integer start)
            : func_{func}, stepSize_{Type{1.0} / steps}, base_{base}, scale_{scale}, currentStep_{start} {}

        constexpr Type operator*() const { return scale_ * func_(stepSize_ * currentStep_) + base_; }

        constexpr iterator &operator++() {
            ++currentStep_;
            return *this;
        }

        constexpr iterator operator++(int) {
            iterator temp = *this;
            ++currentStep_;
            return temp;
        }

        constexpr bool operator!=(const iterator &other) const {
            return (currentStep_ != other.currentStep_);
        }

      private:
        Function func_;
        Type stepSize_{0};
        Type base_{0};
        Type scale_{0};
        Integer currentStep_{0};
    };

    GRamp(Function func, Integer steps, Type scale = 1.0, Type base = 0.0)
        : func_{func}, steps_{steps}, scale_{scale}, base_{base} {};

    constexpr iterator begin() { return iterator{func_, steps_, base_, scale_, 0}; }
    constexpr iterator end() { return iterator{func_, steps_, base_, scale_, steps_}; }

    constexpr iterator begin() const { return iterator{func_, steps_, base_, scale_, 0}; }
    constexpr iterator end() const { return iterator{func_, steps_, base_, scale_, steps_}; }

    constexpr static Type flat(Type v) { return 1.0; }
    constexpr static Type linear(Type v) { return v; }
    constexpr static Type cos(Type v) { return std::cos(v * std::numbers::pi / 2); }
    constexpr static Type sin(Type v) { return std::sin(v * std::numbers::pi / 2); }

  private:
    Function func_;
    Integer steps_{0};
    Type scale_{0};
    Type base_{0};
};

} // namespace gbase