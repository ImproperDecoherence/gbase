
#include "gexceptions.hpp"
#include "glogger.hpp"
#include "gprinttools.hpp"
#include "testframework.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

    gbase::GLogger &logger = gbase::GLogger::getInstance();
    logger.setLogLevel(gbase::GLogger::LogLevel::Normal);

    try {
        gtest::TestFramework::getInstance().executeTests();
    } catch (const gbase::GException &exception) {
        std::cout << gbase::CoutColor::Magenta << exception << std::endl;
    }

    return 0;
}
