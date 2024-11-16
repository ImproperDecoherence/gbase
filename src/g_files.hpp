#pragma once

#include <filesystem>
#include <ranges>

#include "g_basic_types.hpp"

namespace gbase {

using GPath = std::filesystem::path;
using GShallowDirIter = std::filesystem::directory_iterator;
using GRecursiveDirIter = std::filesystem::recursive_directory_iterator;

class GDirectory {
  public:
    explicit GDirectory(const GPath path)
        : path_{path}, shallowBegin_{std::filesystem::begin(GShallowDirIter(path_))},
          shallowEnd_{std::filesystem::end(GShallowDirIter(path_))},
          recursiveBegin_{std::filesystem::begin(GRecursiveDirIter(path_))},
          recursiveEnd_{std::filesystem::end(GRecursiveDirIter(path_))} {}

    ~GDirectory() = default;

    auto shallowView() { return std::ranges::subrange(shallowBegin_, shallowEnd_); }
    auto recursiveView() { return std::ranges::subrange(recursiveBegin_, recursiveEnd_); }

  private:
    GPath path_;
    GShallowDirIter shallowBegin_;
    GShallowDirIter shallowEnd_;
    GRecursiveDirIter recursiveBegin_;
    GRecursiveDirIter recursiveEnd_;
};

constexpr auto hasExtension(const String &extension) {
    return std::ranges::views::filter([=](const GPath &path) { return path.extension() == extension; });
}

constexpr auto isFile =
    std::ranges::views::filter([](const GPath &path) { return std::filesystem::is_regular_file(path); });

constexpr auto isDirectory =
    std::ranges::views::filter([](const GPath &path) { return std::filesystem::is_directory(path); });

} // namespace gbase
