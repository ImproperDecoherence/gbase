
#include <numbers>

#include "ggeometry.hpp"
#include "glogger.hpp"
#include "testframework.hpp"

using namespace gbase;

namespace test {

using namespace gbase;

GTEST(GGeometryTest) {

    const double tolerance{10e-7};

    const GDirection d000_000 = GDirection::fromDegrees(0.0, 0.0);
    const GDirection d045_000 = GDirection::fromDegrees(45.0, 0.0);
    const GDirection d090_000 = GDirection::fromDegrees(90.0, 0.0);
    const GDirection d135_000 = GDirection::fromDegrees(135.0, 0.0);
    const GDirection d180_000 = GDirection::fromDegrees(180.0, 0.0);
    const GDirection d225_000 = GDirection::fromDegrees(225.0, 0.0);
    const GDirection d270_000 = GDirection::fromDegrees(270.0, 0.0);
    const GDirection d315_000 = GDirection::fromDegrees(315.0, 0.0);
    const GDirection d360_000 = GDirection::fromDegrees(360.0, 0.0);

    const GDirection d000_m90 = GDirection::fromDegrees(0.0, -90.0);
    const GDirection d045_m45 = GDirection::fromDegrees(45.0, -45.0);
    const GDirection d090_p45 = GDirection::fromDegrees(90.0, +45.0);
    const GDirection d000_p90 = GDirection::fromDegrees(0.0, +90.0);

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
}

} // namespace test