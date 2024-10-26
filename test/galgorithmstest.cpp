#include <iostream>

#include "galgorithms.hpp"
#include "testframework.hpp"

using namespace std;

namespace gbase::test {

GTEST(GAlgorithmsTest) {
    const GVector d1 = {'A', 'B', 'C', 'D'};
    const GVector<GSet<Char>> e1 = {{'A', 'B'}, {'A', 'C'}, {'A', 'D'},
                                       {'B', 'C'}, {'B', 'D'}, {'C', 'D'}};
    const GVector r1 = combinations(d1, 2);
    GCHECK("Combinations", r1, e1);
}

} // namespace gbase::test