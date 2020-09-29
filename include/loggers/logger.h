#ifndef ZLOG_DETAILS_LOGGER_H_
#define ZLOG_DETAILS_LOGGER_H_
#include <string>

namespace zlog {

class Logger {
public:
    Logger(const std::string& name, Level lvl = INFO) : name(name), lvl(lvl) {}
    virtual ~Logger() {}
    virtual void Write(const std::string& msg, Level lvl)
    {
        if (lvl < this->lvl) {
            return;
        }
        data += msg;
    }

    virtual void Send() {}

    void SetLevel(Level lvl)
    {
        this->lvl = lvl;
    }

    Level GetLevel()
    {
        return lvl;
    }

    std::string GetName()
    {
        return name;
    }

protected:
    std::string data;
    std::string name;
    Level lvl;
};

}  // namespace zlog

#endif  // ZLOG_DETAILS_LOGGER_H_