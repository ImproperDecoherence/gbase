#include <sstream>

#include "gset.hpp"
#include "testframework.hpp"

namespace gbase::test {

GTEST(GSetTest) {
    GSet v1 = {'A', 'B', 'C', 'D'};
    GCHECK("Contains 1", v1.contains('A'), true);
    GCHECK("Contains 2", v1.contains('F'), false);

    GSet v2{v1};
    GCHECK("Copy constructor", v2, v1);

    std::stringstream ss{""};
    v1.print(ss);
    const String expectedPrint{"[A, B, C, D]"};
    GCHECK("Print", ss.str(), expectedPrint);

    const GSet constUnsorted = {'B', 'A', 'D', 'C'};
    const GSet expectedSorted = {'A', 'B', 'C', 'D'};
    GCHECK("Const sort", constUnsorted, expectedSorted);

    GSet toBeExtended{'A', 'C', 'D'};
    toBeExtended += 'B';
    GCHECK("Extend 1", toBeExtended, GSet{'A', 'B', 'C', 'D'});

    const GSet extendVector{'E', 'F'};
    toBeExtended += extendVector;
    GCHECK("Extend 2", toBeExtended, GSet{'A', 'B', 'C', 'D', 'E', 'F'});
}

} // namespace gbase::test