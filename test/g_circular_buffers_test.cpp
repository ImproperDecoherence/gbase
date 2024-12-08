#include <iostream>

#include "g_circular_buffers.hpp"
#include "g_test_framework.hpp"
#include "g_vector.hpp"

using namespace std;
using namespace gbase;

namespace gbase::test {

GTEST(GCircularBuffersTest) {
    const GVector d1 = {'A', 'B', 'C'};
    const GVector e1 = {'A', 'B', 'C', 'A', 'B'};
    GCircularVectorIterator iter{d1};

    for (Unsigned i = 0; i < e1.size(); ++i) {
        GCHECK("circular vector iterator", *iter, e1[i]);
        ++iter;
    }
}

} // namespace gbase::test