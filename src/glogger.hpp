#include <iostream>
#include <vector>

#include "gbasictypes.hpp"
#include "gprinttools.hpp"
#include "gstringtools.hpp"

using namespace std;

class GLogger {
  public:
    static GLogger &getInstance() {
        static GLogger instance;
        return instance;
    }

    void enableLogger(bool enable) { loggerEnabled_ = enable; }

    void addFilter(const String &trigger) { infoLogFilter_.emplace_back(trigger); }

    void info(const String &message) {
        if (loggerEnabled_) {
            cout << CoutColor::Green;
            cout << "INFO: ";
            cout << CoutColor::Reset;
            cout << message << endl;
        }
    }

    void warning(const String &message) {
        if (infoLogEnabled(message)) {
            cout << CoutColor::Yellow;
            cout << "WARNING: ";
            cout << CoutColor::Reset;
            cout << message << endl;
        }
    }

  private:
    bool infoLogEnabled(const String &context) const {
        bool infoEnabled = false;
        for (auto f : infoLogFilter_) {
            if (context.contains(f)) {
                infoEnabled = true;
                break;
            }
        }
        return loggerEnabled_ && infoEnabled;
    }

    bool loggerEnabled_ = false;
    vector<String> infoLogFilter_;
};

#define GLOG_INFO(...)                                                                                       \
    do {                                                                                                     \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << concatToString(__VA_ARGS__);                                                                  \
        GLogger::getInstance().info(oss.str());                                                              \
    } while (false);

#define GLOG_WARNING(...)                                                                                    \
    do {                                                                                                     \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << concatToString(__VA_ARGS__);                                                                  \
        GLogger::getInstance().warning(oss.str());                                                           \
    } while (false);
