
#pragma once

#include <functional>

#include "gvector.hpp"

namespace gbase {

class GSignal {
  public:
    GSignal() = default;
    ~GSignal() = default;

    template <typename Object, typename Method> constexpr void connect(Object *object, Method method) {
        auto callback = [=](auto &&...args) { (object->*method)(std::forward<decltype(args)>(args)...); };
        connections_.emplace_back(callback);
    }

    constexpr void emit() {
        for (const auto &connection : connections_) {
            connection();
        }
    }

    template <typename Arg1> constexpr void emit(Arg1 &&arg1) {
        for (const auto &connection : connections_) {
            connection(std::forward<Arg1>(arg1));
        }
    }

    template <typename Arg1, typename Arg2> constexpr void emit(Arg1 &&arg1, Arg2 &&arg2) {
        for (const auto &connection : connections_) {
            connection(std::forward<Arg1>(arg1), std::forward<Arg2>(arg2));
        }
    }

  private:
    GVector<std::function<void()>> connections_;
};

}