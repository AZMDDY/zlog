#ifndef ZLOG_DETAILS_BASE_H_
#define ZLOG_DETAILS_BASE_H_
#include <string>

const bool ZLOG_MUTI_THREADS = true;  // false: 不支持多线程；true: 支持多线程

namespace zlog {

enum Level { DEBUG, INFO, WARNING, ERROR, FATAL, NO_LEVELS };

const char LevelStr[static_cast<int>(NO_LEVELS)] = {'D', 'I', 'W', 'E', 'F'};

}  // namespace zlog
#endif  // ZLOG_DETAILS_BASE_H_