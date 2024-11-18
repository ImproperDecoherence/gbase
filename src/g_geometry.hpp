#pragma once

#include <cmath>
#include <numbers>
#include <ostream>

namespace gbase {

using Radians = double;
using Degrees = double;

constexpr Radians Pi = std::numbers::pi;
constexpr Radians Pi_1_2 = std::numbers::pi / 2;
constexpr Radians Pi_1_3 = std::numbers::pi / 3;
constexpr Radians Pi_1_4 = std::numbers::pi / 4;
constexpr Radians Pi_1_8 = std::numbers::pi / 8;

constexpr Radians degreesToRadians(Degrees angle) { return angle / 180.0 * Pi; }
constexpr Degrees radiansToDegrees(Radians angle) { return angle * 180.0 / Pi; }

namespace Azimuth {
constexpr Radians North = 0.0;
constexpr Radians NorthEast = Pi / 4;
constexpr Radians East = Pi / 2;
constexpr Radians SouthEast = 3 * Pi / 4;
constexpr Radians South = Pi;
constexpr Radians SouthWest = 5 * Pi / 4;
constexpr Radians West = 3 * Pi / 2;
constexpr Radians NorthWest = 7 * Pi * 4;
} // namespace Azimuth

namespace Elevation {
constexpr Radians Up = Pi / 2;
constexpr Radians Horizontal = 0;
constexpr Radians Down = -Pi / 2;
} // namespace Elevation

struct GPolarVector2D {
    double radius{0.0};
    Radians theta{0.0}; // the angle counter clockwise from the x-axis
};

struct GCartesianVector2D {
    double x{0.0};
    double y{0.0};
};

constexpr GCartesianVector2D polarToCartesian(const GPolarVector2D &p) {
    return {p.radius * std::cos(p.theta), p.radius * std::sin(p.theta)};
}

constexpr GPolarVector2D cartesianToPolar(const GCartesianVector2D c) {
    return {std::sqrt(c.x * c.x + c.y * c.y), std::atan2(c.y, c.x)};
}

constexpr double operator*(const GCartesianVector2D &a, const GCartesianVector2D &b) {
    return a.x * b.x + a.y * b.y;
}

constexpr double operator*(const GPolarVector2D &a, const GPolarVector2D &b) {
    const auto ca = polarToCartesian(a);
    const auto cb = polarToCartesian(b);
    return ca * cb;
}

struct GPolarDirection3D {
    Radians azimuth{0.0};
    Radians elevation{0.0};
};

struct GCartesianVector3D {
    double x{0.0};
    double y{0.0};
    double z{0.0};
};

constexpr GCartesianVector3D polarToCartesian(const GPolarDirection3D &polarDirection) {
    const double x = std::cos(polarDirection.elevation) * std::cos(polarDirection.azimuth);
    const double y = std::cos(polarDirection.elevation) * std::sin(polarDirection.azimuth);
    const double z = std::sin(polarDirection.elevation);
    return {x, y, z};
}

constexpr GPolarDirection3D cartesianToPolarDirection(const GCartesianVector3D &cartesianDirection) {
    const double azimuth = std::atan2(cartesianDirection.y, cartesianDirection.x);
    const double magnitude =
        std::sqrt(cartesianDirection.x * cartesianDirection.x + cartesianDirection.y * cartesianDirection.y +
                  cartesianDirection.z * cartesianDirection.z);
    double elevation = std::asin(cartesianDirection.z / magnitude);
    return {azimuth, elevation};
}

constexpr double operator*(const GCartesianVector3D &a, const GCartesianVector3D &b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

constexpr double operator*(const GPolarDirection3D &a, const GPolarDirection3D &b) {
    const auto cda = polarToCartesian(a);
    const auto cdb = polarToCartesian(b);
    return cda * cdb;
}

class GDirection3D {
  public:
    GDirection3D() = default;
    GDirection3D(Radians azimuth, Radians elevation)
        : cartDir_{polarToCartesian(GPolarDirection3D{azimuth, elevation})} {};
    GDirection3D(const GPolarDirection3D &polarDir) : cartDir_{polarToCartesian(polarDir)} {}
    GDirection3D(const GCartesianVector3D &cartDir) : cartDir_{cartDir} {}

    double operator*(const GDirection3D &rhs) const { return cartDir_ * rhs.cartDir_; };

    const GCartesianVector3D &cartesian() const { return cartDir_; }
    GPolarDirection3D polar() const { return cartesianToPolarDirection(cartDir_); }

    void setElevation(Radians elevation) {
        GPolarDirection3D updatedPolar = polar();
        updatedPolar.elevation = elevation;
        cartDir_ = polarToCartesian(updatedPolar);
    }

    void setAzimuth(Radians azimuth) {
        GPolarDirection3D updatedPolar = polar();
        updatedPolar.azimuth = azimuth;
        cartDir_ = polarToCartesian(updatedPolar);
    }

    GDirection3D rotated(Radians deltaAzimuth, Radians deltaElevation) const {
        const auto [azimuth, elevation] = polar();
        return GDirection3D{azimuth + deltaAzimuth, elevation + deltaElevation};
    }

  private:
    GCartesianVector3D cartDir_;
};

constexpr std::ostream &operator<<(std::ostream &os, const GPolarDirection3D &d) {
    return os << "GPolarDirection3D{" << radiansToDegrees(d.azimuth) << ", " << radiansToDegrees(d.elevation)
              << "}";
}

constexpr std::ostream &operator<<(std::ostream &os, const GCartesianVector3D &d) {
    return os << "GCartesianVector3D{" << d.x << ", " << d.y << ", " << d.z << "}";
}

constexpr std::ostream &operator<<(std::ostream &os, const GDirection3D &d) {
    const auto polar = d.polar();
    return os << "GDirection3D{" << radiansToDegrees(polar.azimuth) << ", "
              << radiansToDegrees(polar.elevation) << "}";
}

} // namespace gbase
