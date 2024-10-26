#include <iostream>

#include "genumerate.hpp"
#include "gvector.hpp"
#include "testframework.hpp"

using namespace std;

namespace gbase::test {

GTEST(GEnumerateTest) {
    const GVector<Char> characters{'A', 'B', 'C'};

    Size expectedIndex{0};
    for (const auto &[index, value] : GEnumerate(characters)) {
        GCHECK(index, expectedIndex);
        GCHECK(value, characters[expectedIndex]);
        ++expectedIndex;
    }
}

} // namespace gbase::test