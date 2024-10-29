
#pragma once

#include <map>
#include <optional>
#include <ostream>

#include "gbasictypes.hpp"
#include "gvector.hpp"

namespace gbase {

/**
 * @brief A specialization of the std::map.
 */
template <typename Key, typename Value> class GDictionary : private std::map<Key, Value> {
    using base = std::map<Key, Value>;

  public:
    GDictionary() = default;

    GDictionary(std::initializer_list<std::pair<const Key, Value>> initList) : base(initList) {}

    GDictionary(const std::map<Key, Value> &m) : base{m} {}

    ~GDictionary() = default;

    using base::allocator_type;
    using base::const_iterator;
    using base::const_pointer;
    using base::const_reference;
    using base::const_reverse_iterator;
    using base::difference_type;
    using base::insert_return_type;
    using base::iterator;
    using base::key_compare;
    using base::key_type;
    using base::mapped_type;
    using base::node_type;
    using base::pointer;
    using base::reference;
    using base::reverse_iterator;
    using base::value_type;

    using ValueCompare = base::value_compare;

    using base::operator=;
    using base::at;
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
    using base::insert;
    using base::merge;
    using base::rbegin;
    using base::rend;
    using base::size;
    using base::swap;

    constexpr Size maxSize() const { return base::max_size(); };

    /**
     * @brief Customized to raise OutOfRange exception when index out of range
     */
    constexpr const Value &operator[](const Key &key) const { return at(key); }

    /**
     * @brief Customized to raise OutOfRange exception when index out of range
     */
    constexpr Value &operator[](const Key &key) { return at(key); }

    /**
     * @brief Returns a view with all keys.
     */
    constexpr auto keys() const { return *this | std::ranges::views::keys; }

    /**
     * @brief Returns a view with all values.
     */
    constexpr auto values() const { return *this | std::ranges::views::values; }

    /**
     * @brief Returns a view with all values.
     */
    constexpr auto values() { return *this | std::ranges::views::values; }

    /**
     * @brief Returns a vector with all keys.
     */
    constexpr GVector<Key> keyVector() const {
        auto v = keys() | std::ranges::to<std::vector<Key>>();
        return GVector<Key>{v};
    }

    /**
     * @brief Returns a vector with all values.
     */
    constexpr GVector<Value> valueVector() const {
        auto v = values() | std::ranges::to<std::vector<Value>>();
        return GVector<Value>{v};
    }

    /**
     * @brief Searches for the first key with given value.
     * @return The found key as a std::optional, or std::nullopt if no key was found.
     */
    constexpr std::optional<Key> findKeyOfValue(const Value &value) const {
        for (const auto &pair : *this) {
            if (pair.second == value) {
                return pair.first;
            }
        }
        return std::nullopt;
    }

    /**
     * @brief Prints a textual representaion of the dictionary.
     */
    constexpr void print(std::ostream &target) const {
        target << '[';

        if (!empty()) {
            auto it = begin();
            target << it->first << ": " << it->second;
            it++;

            while (it != end()) {
                target << ", " << it->first << ": " << it->second;
                it++;
            }
        }

        target << ']';
    }
};

template <typename Key, typename Value>
std::ostream &operator<<(std::ostream &os, const GDictionary<Key, Value> &dict) {
    dict.print(os);
    return os;
}

} // namespace gbase