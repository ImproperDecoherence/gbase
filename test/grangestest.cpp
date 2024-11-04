
#include <cmath>

#include "glogger.hpp"
#include "granges.hpp"
#include "gvector.hpp"
#include "testframework.hpp"

using namespace gbase;

namespace test {

using namespace gbase;

GTEST(GRangesTest) {

    const double tolerance = 10e-7;

    GCHECKT("lower limit", limit(-7.3, -5.0, 5.0), -5.0, tolerance);
    GCHECKT("upper limit", limit(+7.3, -5.0, 5.0), 5.0, tolerance);

    Integer steps = 0;
    for (const auto x : linearRange(0.0, 10.0, 10)) {
        GCHECKT("A", x, 0.0 + steps * (10.0 - 0.0) / 10, tolerance);
        ++steps;
    }
    GCHECK(steps, 10);

    steps = 0;
    for (const auto x : linearRange(-10.0, 10.0, 10)) {
        GCHECKT("B", x, -10.0 + steps * (10.0 - -10.0) / 10, tolerance);
        ++steps;
    }
    GCHECK(steps, 10);

    steps = 0;
    for (const auto x : linearRange(10.0, -10.0, 10)) {
        GCHECKT("C", x, 10.0 + steps * (-10.0 - 10.0) / 10, tolerance);
        ++steps;
    }
    GCHECK(steps, 10);

    steps = 0;
    for (const auto x : linearRange(0.0, 10.0, 0.5)) {
        GCHECKT("D", x, 0.0 + steps * 0.5, tolerance);
        ++steps;
    }
    GCHECK(steps, 21);

    steps = 0;
    for (const auto x : linearRange(-10.0, 10.0, 1.0)) {
        GCHECKT("E", x, -10.0 + steps * 1.0, tolerance);
        ++steps;
    }
    GCHECK(steps, 21);

    steps = 0;
    for (const auto x : genericRange(-2.0, 2.0, 0.2, [](double v) { return std::sin(v); })) {
        GCHECKT("G", x, std::sin(-2.0 + steps * 0.2), tolerance);
        ++steps;
    }
    GCHECK(steps, 21);
}

} // namespace test