#ifndef ZLOG_LOGGERS_STDERR_LOGGER_H_
#define ZLOG_LOGGERS_STDERR_LOGGER_H_
#include <iostream>
#include "logger.h"

namespace zlog {
class StdErrLogger : public Logger {
public:
    StdErrLogger(const std::string& name, Level lvl = INFO) : Logger(name, lvl) {}
    ~StdErrLogger() {}
    void Write(const std::string& msg, Level lvl) override
    {
        if (lvl < this->lvl) {
            return;
        }
        std::cerr << msg;
    }

private:
};
}  // namespace zlog

#endif  // ZLOG_LOGGERS_STDERR_LOGGER_H_