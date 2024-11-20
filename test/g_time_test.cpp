#include <iostream>

#include "g_logger.hpp"
#include "g_test_framework.hpp"
#include "g_time.hpp"

using namespace std;
using namespace gbase;

namespace gbase::test {

GTEST(GTimeTest) {
    GLocalLogLevel localLogLevel(GLogger::LogLevel::None);

    GUTCTime now = GUTCTime::now();
    GLOG_DETAILS("Time: ", now.timeOfDay().toString());
}

} // namespace gbase::test