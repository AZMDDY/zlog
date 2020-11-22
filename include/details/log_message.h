#ifndef ZLOG_DETTAILS_LOG_MESSAGE_H_
#define ZLOG_DETTAILS_LOG_MESSAGE_H_
#include <chrono>
#include <ctime>
#include <iomanip>
#include <sstream>
#include <string>
#include <thread>
namespace zlog {
namespace details {

    class LogStream;
    class LoggerManage;

    class LogMessage {
    public:
        LogMessage(int line, const std::string& file, Level lvl)
        {
            Init(line, file, lvl);
        }
        ~LogMessage()
        {
            Flush();
        }

        LogStream& Stream()
        {
            return stream;
        }

    private:
        void Init(int line, const std::string& file, Level lvl)
        {
            logLevel = lvl;

            auto now = std::chrono::system_clock::now();
            auto now_s = std::chrono::system_clock::to_time_t(now);
            auto now_ss = std::chrono::system_clock::from_time_t(now_s);
            char timeStamp[20];  // yyyy-mm-dd hh:MM:ss
            std::strftime(timeStamp, sizeof(timeStamp), "%F %T", std::localtime(&now_s));
            int msecs = std::chrono::duration_cast<std::chrono::microseconds>(now - now_ss).count();

            std::stringstream ss;
            ss << std::this_thread::get_id();
            size_t pid = std::stoul(ss.str());

            stream << lvl << ": " << timeStamp << "." << msecs << " " << pid << " " << file << ":" << line << "] ";
        }
        void Flush()
        {
            zlog::LoggerManage::Instance()->Write2Logger(stream.GetData(), logLevel);
        }

    private:
        LogStream stream;
        Level logLevel;
    };

}  // namespace details
}  // namespace zlog

#endif  // ZLOG_DETTAILS_LOG_MESSAGE_H_