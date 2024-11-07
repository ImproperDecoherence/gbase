#pragma once

#include "g_vector.hpp"

namespace gbase {

template <typename Type> class GCircularVectorIterator {

  public:
    explicit GCircularVectorIterator(const GVector<Type> &v)
        : begin_{v.begin()}, iter_{v.begin()}, end_{v.end()} {}

    constexpr const Type &operator*() const { return *iter_; }

    GCircularVectorIterator operator++() {
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
    typename GVector<Type>::const_iterator begin_;
    typename GVector<Type>::const_iterator iter_;
    typename GVector<Type>::const_iterator end_;
};

} // namespace gbase