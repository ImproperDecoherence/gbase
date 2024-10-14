#include <algorithm>
#include <numeric>
#include <ranges>

#include "gbasictypes.hpp"
#include "gvector.hpp"

#pragma once

template <std::ranges::range Range> constexpr auto combinations(const Range &input, Size subsequenceLength) {
    using ValueType = typename std::ranges::range_value_t<Range>;

    const auto inputSize = std::ranges::distance(input);

    GVector<GVector<ValueType>> result;
    GVector<Size> indices(subsequenceLength);

    // Initialize indices to [0, 1, 2, ..., subsequenceLength-1]
    std::iota(indices.begin(), indices.end(), 0);

    do {
        // Create combination using current indices
        GVector<ValueType> combination;
        for (Size i : indices) {
            combination.pushBack(input[i]);
        }
        result.pushBack(combination);

        // Generate the next combination
        Size i = subsequenceLength;
        while (i > 0 && indices[i - 1] == inputSize - subsequenceLength + (i - 1)) {
            --i;
        }
        if (i == 0) {
            break;
        }
        ++indices[i - 1];
        for (Size j = i; j < subsequenceLength; ++j) {
            indices[j] = indices[j - 1] + 1;
        }

    } while (indices[0] < input.size() - subsequenceLength + 1);

    return result;
}
