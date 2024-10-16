
#pragma once

#include <algorithm>
#include <functional>
#include <ranges>
#include <set>

#include "gbasictypes.hpp"

namespace gbase {

template <typename Type> class GSet : private std::set<Type> {
  private:
    using base = std::set<Type>;

    constexpr static bool defaultCompare(const Type &a, const Type &b) { return a < b; };

  public:
    using base::set; // Using default set constructors.

    GSet(std::initializer_list<Type> initList) : base(initList) {}

    template <InputIteratorOf<Type> InputIt> GSet(InputIt first, InputIt last) : base(first, last){};

    template <RangeOf<Type> Range>
    explicit GSet(const Range &range) : base(std::ranges::begin(range), std::ranges::end(range)){};

    template <RangeOf<Type> Range>
    explicit GSet(Range &&range) : base(std::ranges::begin(range), std::ranges::end(range)){};

    ~GSet() = default;

    template <RangeOf<Type> Range> constexpr const GSet &operator=(const Range &range) {
        clear();
        emplace(range.begin(), range.end());
        return *this;
    }

    // Default vector member types
    using base::allocator_type;
    using base::const_iterator;
    using base::const_pointer;
    using base::const_reference;
    using base::const_reverse_iterator;
    using base::difference_type;
    using base::iterator;
    using base::key_compare;
    using base::key_type;
    using base::node_type;
    using base::pointer;
    using base::reference;
    using base::reverse_iterator;
    using base::size_type;
    using base::value_compare;
    using base::value_type;

    // Default vector operations
    using base::operator=;

    using base::begin;
    using base::cbegin;
    using base::cend;
    using base::clear;
    using base::contains;
    using base::count;
    using base::crbegin;
    using base::crend;
    using base::emplace;
    using base::empty;
    using base::end;
    using base::erase;
    using base::extract;
    using base::find;
    using base::get_allocator;
    using base::insert;
    using base::max_size;
    using base::merge;
    using base::rbegin;
    using base::rend;
    using base::size;
    using base::swap;

    auto operator<=>(const GSet &other) const = default;
    bool operator==(const GSet &other) const = default;
    bool operator!=(const GSet &other) const = default;

    constexpr Size maxSize() const { return base::max_size(); };

    constexpr void extend(const Type &newValue) { insert(newValue); }

    constexpr void operator+=(const Type &newValue) { extend(newValue); }

    constexpr void operator-=(const Type &newValue) { erase(newValue); }

    template <RangeOf<Type> Range> constexpr void extend(const Range &values) {
        for (const auto value : values) {
            insert(value);
        }
    }

    template <RangeOf<Type> Range> constexpr void erase(const Range &values) {
        for (auto value : values) {
            erase(value);
        }
    }

    template <RangeOf<Type> Range> constexpr void operator+=(const Range &values) { extend(values); }

    constexpr void extend(std::initializer_list<Type> initList) {
        for (auto value : initList) {
            insert(value);
        }
    }

    constexpr void operator+=(std::initializer_list<Type> initList) { extend(initList); }

    template <RangeOf<Type> Range> constexpr void operator-=(const Range &values) { erase(values); }

    void constexpr print(std::ostream &target) const {
        target << '[';

        if (!empty()) {
            auto it = begin();
            target << *it++;

            while (it != end()) {
                target << ", " << *it++;
            }
        }

        target << ']';
    }
};

template <typename Type> constexpr GSet<Type> operator+(const GSet<Type> &set, const Type &value) {
    GSet<Type> copy{set};
    copy += value;
    return copy;
}

template <typename Type> constexpr GSet<Type> operator-(const GSet<Type> &set, const Type &value) {
    GSet<Type> copy{set};
    copy -= value;
    return copy;
}

template <typename Type, RangeOf<Type> Range>
constexpr GSet<Type> operator+(const GSet<Type> &set, const Range &range) {
    GSet<Type> copy{set};
    copy.extend(range);
    return copy;
}

template <typename Type, RangeOf<Type> Range>
constexpr GSet<Type> operator-(const GSet<Type> &set, const Range &range) {
    GSet<Type> copy{set};
    copy.erase(range);
    return copy;
}

template <typename Type> constexpr std::ostream &operator<<(std::ostream &s, const GSet<Type> &v) {
    v.print(s);
    return s;
}

}