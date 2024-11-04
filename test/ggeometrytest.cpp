
#include <numbers>

#include "ggeometry.hpp"
#include "glogger.hpp"
#include "testframework.hpp"

using namespace gbase;

namespace test {

using namespace gbase;

GTEST(GGeometryTest) {

    const double tolerance{10e-7};

    GCHECKT("degees to radians", degreesToRadians(45.0), Pi / 4, tolerance);
    GCHECKT("radians to degrees", radiansToDegrees(Pi / 2), 90.0, tolerance);

    const GDirection3D d000_000 = GDirection3D(degreesToRadians(0.0), degreesToRadians(0.0));
    const GDirection3D d045_000 = GDirection3D(degreesToRadians(45.0), degreesToRadians(0.0));
    const GDirection3D d090_000 = GDirection3D(degreesToRadians(90.0), degreesToRadians(0.0));
    const GDirection3D d135_000 = GDirection3D(degreesToRadians(135.0), degreesToRadians(0.0));
    const GDirection3D d180_000 = GDirection3D(degreesToRadians(180.0), degreesToRadians(0.0));
    const GDirection3D d225_000 = GDirection3D(degreesToRadians(225.0), degreesToRadians(0.0));
    const GDirection3D d270_000 = GDirection3D(degreesToRadians(270.0), degreesToRadians(0.0));
    const GDirection3D d315_000 = GDirection3D(degreesToRadians(315.0), degreesToRadians(0.0));
    const GDirection3D d360_000 = GDirection3D(degreesToRadians(360.0), degreesToRadians(0.0));
    const GDirection3D d000_m90 = GDirection3D(degreesToRadians(0.0), degreesToRadians(-90.0));
    const GDirection3D d045_m45 = GDirection3D(degreesToRadians(45.0), degreesToRadians(-45.0));
    const GDirection3D d090_p45 = GDirection3D(degreesToRadians(90.0), degreesToRadians(45.0));
    const GDirection3D d000_p90 = GDirection3D(degreesToRadians(0.0), degreesToRadians(90.0));

    GCHECKT("A1", d000_000 * d000_000, 1.0, tolerance);
    GCHECKT("A2", d000_000 * d045_000, 1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("A3", d000_000 * d090_000, 0.0, tolerance);
    GCHECKT("A4", d000_000 * d135_000, -1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("A5", d000_000 * d180_000, -1.0, tolerance);
    GCHECKT("A6", d000_000 * d225_000, -1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("A7", d000_000 * d270_000, 0.0, tolerance);
    GCHECKT("A8", d000_000 * d315_000, 1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("A9", d000_000 * d360_000, 1.0, tolerance);

    GCHECKT("E1", d000_000 * d000_m90, 0.0, tolerance);
    GCHECKT("E2", d045_000 * d045_m45, 1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("E3", d000_000 * d000_000, 1.0, tolerance);
    GCHECKT("E4", d090_000 * d090_p45, 1.0 / std::numbers::sqrt2, tolerance);
    GCHECKT("E5", d000_000 * d000_p90, 0.0, tolerance);

    GCHECKT("polar azimuth", d090_p45.polar().azimuth, degreesToRadians(90.0), tolerance);
    GCHECKT("polar elevation", d090_p45.polar().elevation, degreesToRadians(45.0), tolerance);

    GDirection3D d1{0.0, 0.0};
    d1.setAzimuth(0.5);
    d1.setElevation(-0.2);
    GCHECKT("set azimuth", d1.polar().azimuth, 0.5, tolerance);
    GCHECKT("set elevation", d1.polar().elevation, -0.2, tolerance);
}

} // namespace test