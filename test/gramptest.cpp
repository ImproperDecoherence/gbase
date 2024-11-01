
#include "gramp.hpp"
#include "glogger.hpp"
#include "gvector.hpp"
#include "testframework.hpp"

using namespace gbase;

namespace test {

using namespace gbase;

GTEST(GRampTest) {

    constexpr Integer numberOfSteps{10};
    constexpr double stepSize{1.0 / numberOfSteps};
    constexpr double tolerance{10e-7};
    double expectedValue{0.0};
    Integer steps{0};

    for (auto value : GRamp<double>{GRamp<double>::linear, numberOfSteps}) {
        expectedValue = steps * stepSize;
        GCHECKT("linear up", value, expectedValue, tolerance);
        ++steps;
    }
    GCHECK(steps, numberOfSteps);

    steps = 0;
    for (auto value : GRamp<double>{GRamp<double>::linear, numberOfSteps, -1.0, 1.0}) {
        expectedValue = 1.0 - steps * stepSize;
        GCHECKT("linear down", value, expectedValue, tolerance);
        ++steps;
    }
    GCHECK(steps, numberOfSteps);

    steps = 0;
    for (auto value : GRamp<double>{GRamp<double>::linear, numberOfSteps, 10.0, 2.0}) {
        expectedValue = 2.0 + 10.0 * steps * stepSize;
        GCHECKT("linear up scaled", value, expectedValue, tolerance);
        ++steps;
    }
    GCHECK(steps, numberOfSteps);

    steps = 0;
    for (auto value : GRamp<double>{GRamp<double>::sin, numberOfSteps}) {
        expectedValue = std::sin(steps * stepSize * std::numbers::pi / 2);
        GCHECKT("sin", value, expectedValue, tolerance);
        ++steps;
    }
    GCHECK(steps, numberOfSteps);
}

} // namespace test