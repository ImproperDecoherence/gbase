
#pragma once

#include <iomanip>
#include <iostream>
#include <type_traits>
#include <vector>

#include "g_basic_types.hpp"
#include "g_exceptions.hpp"

namespace gbase {

/**
 * @brief Namespace with color codes for std::cout.
 */
namespace CoutColor {
constexpr String Black{"\033[30m"};
constexpr String Red{"\033[31m"};
constexpr String Green{"\033[32m"};
constexpr String Yellow{"\033[33m"};
constexpr String Blue{"\033[34m"};
constexpr String Magenta{"\033[35m"};
constexpr String Cyan{"\033[36m"};
constexpr String White{"\033[37m"};

constexpr String Reset{"\033[0m"};
} // namespace CoutColor

/**
 * @brief Help function to printTableRow().
 */
template <typename Type>
constexpr void printRowColumn(Integer width, const String &color, const Type &element) {
    std::cout << color;
    std::cout << std::setw(width) << element;
    std::cout << CoutColor::Reset;
}

/**
 * @brief Prints a table row to std::cout.
 *
 * @param columnWidths A vector with column widths - the size must match number of Args.
 * @param colors A vector with CoutColor codes for each cloumn - the size must match number of Args.
 * @param args Each argument corresponds to a column value.
 */
template <typename... Args>
constexpr void printTableRow(const std::vector<Integer> &columnWidths, const std::vector<String> &colors,
                             Args... args) {
    std::ios_base::fmtflags savedCoutFlags(std::cout.flags());

    if (sizeof...(args) != columnWidths.size() || columnWidths.size() != colors.size()) {
        GTHROW(GInvalidArgument,
               "Number of widths and colors must match the number of arguments: ", columnWidths.size(), ", ",
               colors.size());
    }

    Integer columnIndex{0};
    Integer colorIndex{0};
    std::cout << std::right;
    (printRowColumn(columnWidths[columnIndex++], colors[colorIndex++], args), ...);
    std::cout << std::endl;

    std::cout.flags(savedCoutFlags); // restore cout formatting
}

template <typename T> void printPointer(std::ostream &os, const T *ptr) {
    static_assert(std::is_pointer<T *>::value, "Input must be a pointer.");

    // Save the current stream format
    auto flags = os.flags(); // Save format flags
    auto fill = os.fill();   // Save fill character

    os << std::hex << std::showbase << std::internal << std::setw(sizeof(void *) * 2 + 2) << std::setfill('0')
       << (uintptr_t)ptr;

    // Restore the original stream format
    os.flags(flags); // Restore format flags
    os.fill(fill);   // Restore fill character
}

} // namespace gbase
