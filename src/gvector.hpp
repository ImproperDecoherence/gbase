
#pragma once

#include <algorithm>
#include <functional>
#include <iostream>
#include <ranges>
#include <vector>

#include "gbasictypes.hpp"

namespace gbase {

/**
 * @brief Template class based on std::vector but with some additions and modificatons.
 */
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

    /**
     * @brief Custimized to raise an exception when index is out of range.
     */
    const Type &operator[](const Size &index) const { return at(index); }

    /**
     * @brief Custimized to raise an exception when index is out of range.
     */
    Type &operator[](const Size &index) { return at(index); }

    /**
     * @brief Searches for a value in the vector.
     * @return The index of the first value found, or -1 if the value was not found.
     */
    constexpr Integer find(const Type &value) const {
        for (Size i = 0; i < size(); ++i) {
            if (at(i) == value) {
                return i;
            }
        }

        return -1;
    }

    /**
     * @brief Appends the provided value to the end of the vector.
     */
    constexpr void extend(const Type &newValue) { pushBack(newValue); }

    /**
     * @brief Appends the provided value to the end of the vector.
     */
    constexpr void operator+=(const Type &newValue) { extend(newValue); }

    /**
     * @brief Appends the provided value to a copy of this vector and returns the result.
     */
    constexpr GVector<Type> operator+(const Type &newValue) {
        GVector<Type> copy{*this};
        copy.extend(newValue);
        return copy;
    }

    /**
     * @brief Appends the provided range to the end of the vector.
     */
    template <RangeOf<Type> Range> constexpr void extend(const Range &values) {
        insert(end(), values.begin(), values.end());
    }

    /**
     * @brief Appends the provided range to the end of the vector.
     */
    template <RangeOf<Type> Range> constexpr void operator+=(const Range &values) { extend(values); }

    /**
     * @brief Appends the provided range to a copy of this vector and returns the result.
     */
    template <RangeOf<Type> Range> constexpr GVector<Type> operator+(const Range &values) const {
        GVector<Type> copy{*this};
        copy.extend(values);
        return copy;
    }

    /**
     * @brief Appends the provided initializer list to the end of the vector.
     */
    constexpr void extend(std::initializer_list<Type> initList) {
        insert(end(), initList.begin(), initList.end());
    }

    /**
     * @brief Appends the provided initializer list to the end of the vector.
     */
    constexpr void operator+=(std::initializer_list<Type> initList) { extend(initList); }

    /**
     * @brief Appends the provided initializer list to a copy of this vector and returns the result.
     */
    constexpr const GVector<Type> operator+(std::initializer_list<Type> initList) const {
        GVector<Type> copy{*this};
        copy.insert(copy.end(), initList.begin(), initList.end());
    }

    /**
     * @brief Sorts the contents of this vector.
     *
     * @param compareFn The default sort function is 'a < b', i.e. ascending order.
     */
    void constexpr sort(std::function<bool(Type, Type)> compareFn = defaultCompare) {
        std::ranges::sort(*this, compareFn);
    }

    /**
     * @brief Returns a sorted copy of this vector.
     *
     * @param compareFn The default sort function is 'a < b', i.e. ascending order.
     */
    GVector<Type> constexpr sort(std::function<bool(Type, Type)> compareFn = defaultCompare) const {
        GVector result{*this};
        std::ranges::sort(result, compareFn);
        return result;
    }

    /**
     * @brief Circular rotation of the contents of the vector.
     *
     * @param steps Rotates to the right for positive steps and to the left for negative steps.
     */
    void constexpr rotate(Integer steps) {
        steps = steps % static_cast<Integer>(size());

        if (steps == 0) {
            return;
        }

        if (steps > 0) {
            // Rotate right
            std::rotate(rbegin(), rbegin() + steps, rend());
            return;
        }

        // Rotate left
        std::rotate(begin(), begin() - steps, end());
    }

    /**
     * @brief Prints a textual representation of the vector.
     */
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

} // namespace gbase