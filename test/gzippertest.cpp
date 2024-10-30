#include <iostream>
#include <ranges>

#include "gvector.hpp"
#include "gzipper.hpp"
#include "testframework.hpp"

using namespace std;

namespace gbase::test {

GTEST(GZipperTest) {
    const std::vector<Char> characters{'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I'};
    const std::vector<Integer> integers{1, 2, 3, 4, 5, 6, 7, 8, 9};

    Integer index{0};
    for (const auto &[value1, value2] : GZipper(characters, integers)) {
        GCHECK(value1, characters[index]);
        GCHECK(value2, integers[index]);
        ++index;
    }

    auto add2 = std::ranges::views::transform([](Integer i) { return i + 2; });

    index = 0;
    for (const auto &[value1, value2] : GZipper(characters, integers | add2)) {
        GCHECK(value1, characters[index]);
        GCHECK(value2, integers[index] + 2);
        ++index;
    }

    auto largeInt = std::ranges::views::filter([](Integer i) { return i > 4; });
    auto largeChar = std::ranges::views::filter([](Char c) { return c > 'D'; });

    index = 0;
    for (const auto &[value1, value2] : GZipper(characters | largeChar, integers | largeInt)) {
        GCHECK(value1, characters[index + 4]);
        GCHECK(value2, integers[index + 4]);
        ++index;
    }
}

} // namespace gbase::test