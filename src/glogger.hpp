
#pragma once

#include <iostream>
#include <vector>

#include "gbasictypes.hpp"
#include "gprinttools.hpp"
#include "gstringtools.hpp"

using namespace std;

namespace gbase {

class GLogger {
  public:
    enum class LogLevel { None, Normal, Details };

    static GLogger &getInstance() {
        static GLogger instance;
        return instance;
    }

    constexpr void setLogLevel(LogLevel logLevel) { currentLogLevel_ = logLevel; }

    constexpr LogLevel currentLogLevel() const { return currentLogLevel_; }

    constexpr void addFilter(const String &trigger) { logFilter_.emplace_back(trigger); }

    constexpr void setFilter(const vector<String> &filter) { logFilter_ = filter; }

    constexpr auto currentFilter() const { return logFilter_; }

    constexpr void info(const String &message, LogLevel logLevel = LogLevel::Normal) {
        if (logLevel > currentLogLevel_)
            return;

        if (matchLogFilter(message)) {
            cout << CoutColor::Green;
            cout << "INFO: ";
            cout << CoutColor::Reset;
            cout << message << endl;
        }
    }

    constexpr void warning(const String &message, LogLevel logLevel = LogLevel::Normal) {
        if (logLevel > currentLogLevel_)
            return;

        if (matchLogFilter(message)) {
            cout << CoutColor::Yellow;
            cout << "WARNING: ";
            cout << CoutColor::Reset;
            cout << message << endl;
        }
    }

  private:
    constexpr bool matchLogFilter(const String &context) const {
        if (logFilter_.empty()) {
            return true;
        }

        bool match = false;
        for (auto f : logFilter_) {
            if (context.contains(f)) {
                match = true;
                break;
            }
        }
        return match;
    }

    LogLevel currentLogLevel_ = LogLevel::Normal;
    vector<String> logFilter_;
};

class GLocalLogLevel {
  public:
    GLocalLogLevel(GLogger::LogLevel localLogLevel) {
        previousLogLevel_ = GLogger::getInstance().currentLogLevel();
        GLogger::getInstance().setLogLevel(localLogLevel);
    }

    ~GLocalLogLevel() { GLogger::getInstance().setLogLevel(previousLogLevel_); }

  private:
    GLogger::LogLevel previousLogLevel_;
};

class GLocalLogFilter {
  public:
    GLocalLogFilter(GLogger::LogLevel localLogLevel) {
        previousLogFilter_ = GLogger::getInstance().currentFilter();
        GLogger::getInstance().setLogLevel(localLogLevel);
    }

    ~GLocalLogFilter() { GLogger::getInstance().setFilter(previousLogFilter_); }

  private:
    vector<String> previousLogFilter_;
};

#define GLOG_INFO(...)                                                                                       \
    if (GLogger::getInstance().currentLogLevel() >= GLogger::LogLevel::Normal) {                             \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << concatToString(__VA_ARGS__);                                                                  \
        GLogger::getInstance().info(oss.str(), GLogger::LogLevel::Normal);                                   \
    }

#define GLOG_DETAILS(...)                                                                                    \
    if (GLogger::getInstance().currentLogLevel() >= GLogger::LogLevel::Details) {                            \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << concatToString(__VA_ARGS__);                                                                  \
        GLogger::getInstance().info(oss.str(), GLogger::LogLevel::Details);                                  \
    }

#define GLOG_WARNING(...)                                                                                    \
    {                                                                                                        \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << concatToString(__VA_ARGS__);                                                                  \
        GLogger::getInstance().warning(oss.str());                                                           \
    }

} // namespace gbase