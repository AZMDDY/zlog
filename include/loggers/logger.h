#ifndef ZLOG_DETAILS_LOGGER_H_
#define ZLOG_DETAILS_LOGGER_H_
#include <string>
#include "base.h"
namespace zlog {

class Logger {
public:
    Logger(const std::string& name, Level level) : name(name), lvl(level) {}
    virtual ~Logger() = default;
    virtual void Write(const std::string& msg, Level level)
    {
        if (level < lvl) {
            return;
        }
        data += msg;
    }

    virtual void Send() {}

    void SetLevel(Level level) { lvl = level; }

    Level GetLevel() { return lvl; }

    std::string GetName() { return name; }

protected:
    std::string data;
    std::string name;
    Level lvl;
};

}  // namespace zlog

#endif  // ZLOG_DETAILS_LOGGER_H_