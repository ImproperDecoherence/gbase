#pragma once

#include <iterator>

namespace gbase {

template <typename Container> class GCircularVectorIterator {

  public:
    using Iterator = typename Container::const_iterator;
    using ValueType = typename Container::value_type;

    explicit GCircularVectorIterator(const Container &container)
        : begin_{std::cbegin(container)}, iter_{std::cbegin(container)}, end_{std::cend(container)} {}

    constexpr const ValueType &operator*() const { return *iter_; }

    GCircularVectorIterator &operator++() {
        ++iter_;
        if (iter_ == end_) {
            iter_ = begin_;
        }
        return *this;
    }

    GCircularVectorIterator operator++(int) {
        GCircularVectorIterator temp = *this;
        ++(*this);
        return temp;
    }

  private:
    Iterator begin_;
    Iterator iter_;
    Iterator end_;
};

} // namespace gbase