#include <algorithm>
#include <functional>
#include <ranges>
#include <vector>

#include "gbasictypes.hpp"

#pragma once

template <typename Type> class GVector : private std::vector<Type> {
  private:
    using base = std::vector<Type>;
    constexpr static bool defaultCompare(const Type &a, const Type &b) { return a < b; };

  public:
    using base::vector; // Using standard vector constructors.

    constexpr GVector(std::initializer_list<Type> initList) : base(initList) {}

    template <InputIteratorOf<Type> InputIt>
    constexpr GVector(InputIt first, InputIt last) : base(first, last){};

    template <RangeOf<Type> Range>
    explicit constexpr GVector(const Range &range) : base(std::begin(range), std::end(range)){};

    ~GVector() = default;

    // Default vector member types
    using base::allocator_type;
    using base::const_iterator;
    using base::const_pointer;
    using base::const_reference;
    using base::const_reverse_iterator;
    using base::difference_type;
    using base::iterator;
    using base::pointer;
    using base::reference;
    using base::reverse_iterator;
    using base::size_type;
    using base::value_type;

    // Default vector operations
    using base::operator=;
    using base::assign;
    using base::at;
    using base::back;
    using base::begin;
    using base::capacity;
    using base::cbegin;
    using base::cend;
    using base::clear;
    using base::crbegin;
    using base::crend;
    using base::data;
    using base::emplace;
    using base::empty;
    using base::end;
    using base::erase;
    using base::front;
    using base::get_allocator;
    using base::insert;
    using base::rbegin;
    using base::rend;
    using base::resize;
    using base::size;
    using base::swap;

    constexpr Size maxSize() const { return base::max_size(); };
    constexpr void pushBack(const Type &value) { base::push_back(value); }
    constexpr void emplaceBack(const Type &value) { base::emplace_back(value); }
    constexpr void popBack(const Type &value) { base::pop_back(value); }

    auto operator<=>(const GVector &other) const = default;
    bool operator==(const GVector &other) const = default;
    bool operator!=(const GVector &other) const = default;

    // operator[] is customized to raise OutOfRange exception when index out of range
    const Type &operator[](const Size &index) const { return at(index); }
    Type &operator[](const Size &index) { return at(index); }

    constexpr Integer find(const Type &value) const {
        for (Size i = 0; i < size(); ++i) {
            if (at(i) == value) {
                return i;
            }
        }

        return -1;
    }

    constexpr void extend(const Type &newValue) { pushBack(newValue); }

    constexpr void operator+=(const Type &newValue) { extend(newValue); }

    constexpr GVector<Type> operator+(const Type &newValue) {
        GVector<Type> copy{*this};
        copy.extend(newValue);
        return copy;
    }

    template <RangeOf<Type> Range> constexpr void extend(const Range &values) {
        insert(end(), values.begin(), values.end());
    }

    template <RangeOf<Type> Range> constexpr void operator+=(const Range &values) { extend(values); }

    constexpr void extend(std::initializer_list<Type> initList) {
        insert(end(), initList.begin(), initList.end());
    }

    constexpr void operator+=(std::initializer_list<Type> initList) { extend(initList); }

    template <RangeOf<Type> Range> constexpr GVector<Type> operator+(const Range &values) const {
        GVector<Type> copy{*this};
        copy.extend(values);
        return copy;
    }

    constexpr const GVector<Type> operator+(std::initializer_list<Type> initList) const {
        GVector<Type> copy{*this};
        copy.insert(copy.end(), initList.begin(), initList.end());
    }

    void constexpr sort(std::function<bool(Type, Type)> compareFn = defaultCompare) {
        std::ranges::sort(*this, compareFn);
    }

    GVector<Type> constexpr sort(std::function<bool(Type, Type)> compareFn = defaultCompare) const {
        GVector result{*this};
        std::ranges::sort(result, compareFn);
        return result;
    }

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

template <typename Type> constexpr std::ostream &operator<<(std::ostream &s, const GVector<Type> &v) {
    v.print(s);
    return s;
}
