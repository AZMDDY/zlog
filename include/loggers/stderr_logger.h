#ifndef ZLOG_LOGGERS_STDERR_LOGGER_H_
#define ZLOG_LOGGERS_STDERR_LOGGER_H_
#include <iostream>
#include "logger.h"

namespace zlog {
class StdErrLogger : public Logger {
public:
    StdErrLogger(const std::string& name, Level level = INFO) : Logger(name, level) {}
    ~StdErrLogger() = default;
    void Write(const std::string& msg, Level level) override
    {
        if (level < lvl) {
            return;
        }
        std::cerr << msg;
    }

private:
};
}  // namespace zlog

#endif  // ZLOG_LOGGERS_STDERR_LOGGER_H_