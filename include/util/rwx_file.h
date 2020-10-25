#ifndef ZLOG_UTIL_RWX_FILE_H
#define ZLOG_UTIL_RWX_FILE_H

#include <string>
#include <iostream>
#include <fstream>

namespace zlog {
namespace util {

    enum WriteMode {
        APPEND,  // 追加
        COVER    // 覆盖
    };

    void WriteFile(const std::string& fileName, const std::string& content, WriteMode mode)
    {
        auto openMode = std::ios::binary | std::ios::out;
        switch (mode) {
            case APPEND: {
                openMode |= std::ios::app;
            } break;
            case COVER: {
                openMode |= std::ios::trunc;
            } break;
            default: break;
        }
        std::ofstream ofstrm(fileName, openMode);
        if (!ofstrm.good()) {
            std::cerr << "write error! can't write " << fileName << std::endl;
            return;
        }
        ofstrm.write(content.c_str(), content.size());
    }
}  // namespace util
}  // namespace zlog

#endif  // ZLOG_UTIL_RWX_FILE_H