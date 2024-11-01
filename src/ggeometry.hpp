#pragma once

#include <cmath>
#include <numbers>

namespace gbase {

using Radians = double;
using Degrees = double;

constexpr Radians Pi = std::numbers::pi;

constexpr Radians degreesToRadians(Degrees angle) { return angle / 180.0 * Pi; }
constexpr Degrees radiansToDegress(Radians angle) { return angle * Pi * 180.0; }

static constexpr Radians North = 0.0;
static constexpr Radians East = Pi / 2;
static constexpr Radians South = Pi;
static constexpr Radians West = Pi * 3 / 2;

struct GDirection {
    Radians azimuth;
    Radians elevation;

    static constexpr GDirection fromDegrees(Degrees azimuthDeg, Degrees elevationDeg) {
        return GDirection{.azimuth = degreesToRadians(azimuthDeg),
                          .elevation = degreesToRadians(elevationDeg)};
    }

    constexpr double operator*(const GDirection &r) const {
        return (std::cos(azimuth) * std::cos(elevation)) * (std::cos(r.azimuth) * std::cos(r.elevation)) +
               (std::sin(azimuth) * std::cos(elevation)) * (std::sin(r.azimuth) * (std::cos(r.elevation)) +
                                                            (std::sin(elevation) * std::sin(r.elevation)));
    }
};

} // namespace gbase
