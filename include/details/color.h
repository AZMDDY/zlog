#ifndef ZLOG_DETAILS_COLOR_H_
#define ZLOG_DETAILS_COLOR_H_

#include <string>

namespace zlog {

enum class Color { red, yellow, blue, green, white };

namespace details {

    const std::string color2Ansi[static_cast<int>(Color::white) + 1] = {"\033[31m", "\033[33m", "\033[34m", "\033[32m",
                                                                        "\033[37m"};

    const static std::string disableColor = "\033[0m";

    inline const std::string& Color2Str(Color color)
    {
        return color2Ansi[static_cast<int>(color)];
    }
}  // namespace details
}  // namespace zlog

#endif  // ZLOG_DETAILS_COLOR_H_