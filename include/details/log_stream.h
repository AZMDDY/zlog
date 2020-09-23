#ifndef ZLOG_DETAILS_LOG_STREAM_H_
#define ZLOG_DETAILS_LOG_STREAM_H_
#include <string>

namespace zlog {
namespace details {
    class LogStream {
    public:
        LogStream() = default;
        LogStream(LogStream&) = delete;
        LogStream& operator=(const LogStream&) = delete;

        template <class T>
        LogStream& operator<<(T value)
        {
            data += std::to_string(value);
            return *this;
        }

        LogStream& operator<<(const std::string& value)
        {
            data += value;
            return *this;
        }

        LogStream& operator<<(const char* value)
        {
            data += value;
            return *this;
        }

        LogStream& operator<<(char* value)
        {
            data += value;
            return *this;
        }

        LogStream& operator<<(Color color)
        {
            fmtColor = true;
            data += color2Ansi[static_cast<int>(color)];
            return *this;
        }

        LogStream& operator<<(Level lvl)
        {
            if (lvl < NO_LEVELS) {
                data += LevelStr[static_cast<int>(lvl)];
            }
            return *this;
        }

        std::string& GetData()
        {
            if (fmtColor) {
                data += disableColor;
                fmtColor = false;
            }
            data += '\n';
            return data;
        }

    private:
        std::string data;
        bool fmtColor = false;
    };
}  // namespace details
}  // namespace zlog
#endif  // ZLOG_DETAILS_LOG_STREAM_H_