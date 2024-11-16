#include <iostream>

#include "g_files.hpp"
#include "g_logger.hpp"
#include "g_test_framework.hpp"

using namespace std;
using namespace gbase;

namespace gbase::test {

GTEST(GFilesTest) {
    GLocalLogLevel localLogLevel(GLogger::LogLevel::None);

    GDirectory currentDir("..");
    for (auto path : currentDir.shallowView() | isFile | hasExtension(".hpp")) {
        GLOG_DETAILS(path.path());
    }
}

} // namespace gbase::test