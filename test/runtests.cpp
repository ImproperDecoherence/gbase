
#include "gexceptions.hpp"
#include "glogger.hpp"
#include "gprinttools.hpp"
#include "testframework.hpp"
#include <iostream>

int main(int argc, char *argv[]) {

    GLogger &logger = GLogger::getInstance();
    logger.enableLogger(true);
    logger.addFilter("noteValue");

    try {
        gtest::TestFramework::getInstance().executeTests();
    } catch (const GException &exception) {
        cout << CoutColor::Magenta << exception << endl;
    }

    return 0;
}
