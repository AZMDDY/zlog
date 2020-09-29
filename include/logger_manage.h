#ifndef ZLOG_DETAILS_H_
#define ZLOG_DETAILS_H_

#include <unordered_map>

namespace zlog {
class Mutex;
class Logger;

class LoggerManage {
public:
    static LoggerManage* Instance()
    {
        static LoggerManage instance;
        return &instance;
    }

    void Add(Logger* logger)
    {
        if (logger == nullptr) {
            return;
        }
        loggerMap[logger->GetName()] = logger;
    }

    void Remove(const std::string& loggerName)
    {
        if (loggerMap.find(loggerName) != loggerMap.end()) {
            loggerMap.erase(loggerName);
        }
    }

    void Remove(Logger* logger)
    {
        if (logger == nullptr) {
            return;
        }
        for (auto iter = loggerMap.begin(); iter != loggerMap.end();) {
            if (iter->first == logger->GetName()) {
                iter = loggerMap.erase(iter);
                return;
            }
            else {
                iter++;
            }
        }
    }

    void Write2Logger(const std::string& msg, Level lvl)
    {
        mtx.Lock();
        for (auto& iter : loggerMap) {
            iter.second->Write(msg, lvl);
        }
        mtx.UnLock();
    }

private:
    LoggerManage() = default;
    ~LoggerManage() = default;

private:
    std::unordered_map<std::string, Logger*> loggerMap;
    zlog::details::Mutex mtx;
};

}  // namespace zlog

#endif  // ZLOG_DETAILS_H_