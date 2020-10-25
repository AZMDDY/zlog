#ifndef ZLOG_LOGGERS_SYNC_FILE_LOGGER_H_
#define ZLOG_LOGGERS_SYNC_FILE_LOGGER_H_

#include "base.h"
#include "util/rwx_file.h"
#include "logger.h"

namespace zlog {
class SyncFileLogger : public Logger {
public:
    SyncFileLogger(const std::string& name, Level level) : Logger(name, level) {}
    ~SyncFileLogger() = default;

    void SetLogFileName(const std::string& fileName) { logFileName = fileName; }

    void Write(const std::string& msg, Level level)
    {
        if (level < lvl) {
            return;
        }
        util::WriteFile(logFileName, msg, util::APPEND);
    }

private:
    std::string logFileName;
};

}  // namespace zlog

#endif  // ZLOG_LOGGERS_SYNC_FILE_LOGGER_H_