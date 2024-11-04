
#pragma once

#include <algorithm>
#include <numeric>
#include <ranges>

#include "gbasictypes.hpp"
#include "gexceptions.hpp"
#include "gset.hpp"
#include "gvector.hpp"

namespace gbase {

constexpr Integer nextFactor(const Integer number, Integer factor) {
    while (number % factor != 0) {
        ++factor;
    }
    return factor;
}

constexpr Integer previousFactor(const Integer number, Integer factor) {
    while ((factor > 0) && (number % factor != 0)) {
        --factor;
    }
    return factor;
}

/**
 * @brief Finds all combinations of the input values.
 *
 * @param input A range with the input values.
 * @param subsequenceLength The length of each combination.
 * @return A vector of sets where each set is an unique combination of the input.
 */
template <std::ranges::range Range> constexpr auto combinations(const Range &input, Size subsequenceLength) {
    using ValueType = typename std::ranges::range_value_t<Range>;

    const auto inputSize = std::ranges::distance(input);

    if (subsequenceLength > static_cast<Size>(inputSize)) {
        GTHROW(GInvalidArgument, "Subsequence length must be smaller or equal to the input length.")
    }

    GVector<GSet<ValueType>> result;
    GVector<Size> indices(subsequenceLength);

    // Initialize indices to [0, 1, 2, ..., subsequenceLength-1]
    std::iota(indices.begin(), indices.end(), 0);

    do {
        // Create combination using current indices
        GSet<ValueType> combination;
        for (Size i : indices) {
            combination.extend(input[i]);
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

} // namespace gbase
