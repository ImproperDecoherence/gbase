
#pragma once

#include <iostream>
#include <vector>

#include "g_basic_types.hpp"
#include "g_print_tools.hpp"
#include "g_string_tools.hpp"
#include "g_time.hpp"

using namespace std;

namespace gbase {

/**
 * @brief Singleton class which can be used to handle application logging.
 *
 * Example usage:
 *
 * @code
 * gbase::GLogger &logger = gbase::GLogger::getInstance();
 * logger.setLogLevel(gbase::GLogger::LogLevel::None);
 *
 * GLOG_INFO("Chords in database: ", db.size());
 * GLOG_WARNING("Could not open: ", fileName);
 * GLOG_DETAILS("Adding chord: ", chord);
 * @endcode
 *
 */
class GLogger {
  public:
    enum class LogLevel { None, Normal, Details };

    /**
     * @brief Gives acccess to the singleton instance of the logger.
     */
    static GLogger &getInstance() {
        static GLogger instance;
        return instance;
    }

    void showTimestamp(bool show) { timestamp_ = show; }

    /**
     * @brief Set the logging level. Default is LogLevel::Normal.
     *
     * @param logLevel LogLevel::None: No logging is performed. LogLevel::Normal: INFO logs and WARNING logs
     * are logged. LogLevel::Details. INFO logs, WARNING logs and DETAILED logs are logged.
     */
    constexpr void setLogLevel(LogLevel logLevel) { currentLogLevel_ = logLevel; }

    /**
     * @brief Gives the current log level.
     */
    constexpr LogLevel currentLogLevel() const { return currentLogLevel_; }

    /**
     * @brief Applies a filter to which logs are logged.
     *
     * @param trigger Only logs which 'context' contains the trigger string - or other trigger strings added
     * by this method or setFilter - will be logged. The 'context' includes filename, method/function name or
     * any test in the log message.
     */
    constexpr void addFilter(const String &trigger) { logFilter_.emplace_back(trigger); }

    /**
     * @brief Sets the log filter.
     *
     * @param filter Only logs which context contains the any of the filter strings - or other trigger strings
     * added by this method or setFilter - will be logged. The 'context' includes filename, method/function
     * name or any test in the log message.
     */
    constexpr void setFilter(const vector<String> &filter) { logFilter_ = filter; }

    /**
     * @brief Clears the log filter.
     */
    constexpr void clearFilter() { logFilter_.clear(); }

    /**
     * @brief Returns the current log fileter.
     */
    constexpr auto currentFilter() const { return logFilter_; }

    /**
     * @brief Logs an information message. See also the LOG_INFO macro.
     *
     * @param message The log message.
     * @param logLevel The log will only be captured if logLevel is less or equal to currentLogLevel().
     */
    constexpr void info(const String &message, LogLevel logLevel = LogLevel::Normal) {
        if (logLevel > currentLogLevel_)
            return;

        if (matchLogFilter(message)) {
            if (timestamp_) {
                cout << gbase::GUTCTime::now().timeOfDay().toString() << " | ";
            }
            cout << CoutColor::Green;
            cout << "INFO: ";
            cout << CoutColor::Reset;
            cout << message << endl;
        }
    }

    /**
     * @brief Logs a warning message. See also the LOG_WARNING macro.
     *
     * @param message The log message.
     * @param logLevel The log will only be captured if logLevel is less or equal to currentLogLevel().
     */
    constexpr void warning(const String &message, LogLevel logLevel = LogLevel::Normal) {
        if (logLevel > currentLogLevel_)
            return;

        if (matchLogFilter(message)) {
            cout << CoutColor::Yellow;
            cout << timestamp_ ? (gbase::GUTCTime::now().timeOfDay().toString() + " ") : "";
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
        for (const auto &f : logFilter_) {
            if (context.contains(f)) {
                match = true;
                break;
            }
        }
        return match;
    }

    LogLevel currentLogLevel_ = LogLevel::Normal;
    vector<String> logFilter_;
    bool timestamp_{true};
};

/**
 * @brief Help class to temporary change the current log level within the current scope. The previous log
 * level is restored when the class instance is destroyed.
 *
 * Example usage:
 * @code
 * {
 *   GLocalLogLevel(GLogger::LogLevel::None);
 *   // No logging in this scope.
 * }
 * // Logging will return to global log level setting setting here
 * @endcode
 *
 */
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

/**
 * @brief Help class to temporary change the current log filter within the current scope. The previous log
 * filter is restored when the class instance is destroyed.
 */
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

} // namespace gbase

/**
 * @def GLOG_INFO(...)
 * @brief Captures the file name, the method/function name and given parameters in an info log message with
 * LogLevel::Normal.
 *
 * Example usage:
 * @code
 * GLOG_INFO("The log level was set to: ", logLevel);
 * @endcode
 */
#define GLOG_INFO(...)                                                                                       \
    if (gbase::GLogger::getInstance().currentLogLevel() >= gbase::GLogger::LogLevel::Normal) {               \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << gbase::concatToString(__VA_ARGS__);                                                           \
        gbase::GLogger::getInstance().info(oss.str(), gbase::GLogger::LogLevel::Normal);                     \
    }

/**
 * @def GLOG_DETAILS(...)
 * @brief Captures the file name, the method/function name and given parameters in an info log message with
 * LogLevel::Detailed.
 *
 * Example usage:
 * @code
 * GLOG_DETAILS("Log message: ", message);
 * @endcode
 */
#define GLOG_DETAILS(...)                                                                                    \
    if (gbase::GLogger::getInstance().currentLogLevel() >= gbase::GLogger::LogLevel::Details) {              \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << gbase::concatToString(__VA_ARGS__);                                                           \
        gbase::GLogger::getInstance().info(oss.str(), gbase::GLogger::LogLevel::Details);                    \
    }

/**
 * @def GLOG_WARNING(...)
 * @brief Captures the file name, the method/function name and given parameters in an warning log message with
 * LogLevel::Normal.
 *
 * Example usage:
 * @code
 * GLOG_DETAILS("Log message: ", message);
 * @endcode
 */
#define GLOG_WARNING(...)                                                                                    \
    {                                                                                                        \
        std::ostringstream oss;                                                                              \
        oss << __FILE__ << " | " << __func__ << " | ";                                                       \
        oss << gbase::concatToString(__VA_ARGS__);                                                           \
        gbase::GLogger::getInstance().warning(oss.str(), gbase::GLogger::LogLevel::Normal);                  \
    }
