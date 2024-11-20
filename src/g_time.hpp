#pragma once

#include <chrono>

#include "g_basic_types.hpp"

namespace gbase {

constexpr Integer SecondsPerMinute = 60;
constexpr Integer MillisecondsPerSecond = 1000;
constexpr Integer MillisecondsPerMinute = SecondsPerMinute * MillisecondsPerSecond;

struct GTimeOfDay {
    Integer hours{0};
    Integer minutes{0};
    Integer seconds{0};
    Integer milliseconds{0};

    String toString() const {
        return std::format("{:02d}:{:02d}:{:02d}:{:03d}", hours, minutes, seconds, milliseconds);
    }
};

class GUTCTime {

  public:
    static GUTCTime now() { return GUTCTime{std::chrono::system_clock::now()}; }

    GTimeOfDay timeOfDay() const {
        const auto timeOfDay = timepoint_.time_since_epoch() % std::chrono::days(1);
        const auto hhmmss = std::chrono::hh_mm_ss(timeOfDay);

        return GTimeOfDay{
            // clang-format off
            static_cast<Integer>(hhmmss.hours().count()),
            static_cast<Integer>(hhmmss.minutes().count()),
            static_cast<Integer>(hhmmss.seconds().count()),
            static_cast<Integer>(std::chrono::duration_cast<std::chrono::milliseconds>(hhmmss.subseconds()).count())
            // clang-format on
        };
    }

  private:
    using Timepoint = std::chrono::time_point<std::chrono::system_clock>;

    GUTCTime(const Timepoint &tp) : timepoint_{tp} {}
    Timepoint timepoint_;
};

} // namespace gbase