#include <iostream>
#include <ranges>

#include "genumerate.hpp"
#include "gvector.hpp"
#include "testframework.hpp"

using namespace std;

namespace gbase::test {

GTEST(GEnumerateTest) {
    const std::vector<Char> characters{'A', 'B', 'C'};

    Integer expectedIndex{0};
    for (const auto &[index, value] : GEnumerate(characters)) {
        GCHECK(index, expectedIndex);
        GCHECK(value, characters[expectedIndex]);
        ++expectedIndex;
    }

    const std::vector<Integer> integers{1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto add2 = std::ranges::views::transform([](Integer i) { return i + 2; });

    expectedIndex = 0;
    for (const auto &[index, value] : GEnumerate(integers | add2)) {
        GCHECK(index, expectedIndex);
        GCHECK(value, integers[expectedIndex] + 2);
        ++expectedIndex;
    }

    auto large = std::ranges::views::filter([](Integer i) { return i > 4; });
    expectedIndex = 0;
    for (const auto &[index, value] : GEnumerate(integers | large)) {
        GCHECK(index, expectedIndex);
        GCHECK(value, integers[expectedIndex + 4]);
        ++expectedIndex;
    }
}

} // namespace gbase::test