#ifndef ZLOG_ZLOG_H_
#define ZLOG_ZLOG_H_

#include <cstdarg>
#include <cstdio>
#include <sstream>
#include <string>
#include <thread>
#include "base.h"
#include "details/mutex.h"
#include "details/color.h"
#include "loggers/logger.h"
#include "details/log_stream.h"
#include "logger_manage.h"
#include "details/log_message.h"

#define ZLOG(severity) ZLOG_##severity().Stream()

#define ZLOG_DEBUG() zlog::details::LogMessage(__LINE__, __FILE__, zlog::DEBUG)
#define ZLOG_INFO() zlog::details::LogMessage(__LINE__, __FILE__, zlog::INFO)
#define ZLOG_WARNING() zlog::details::LogMessage(__LINE__, __FILE__, zlog::WARNING)
#define ZLOG_ERROR() zlog::details::LogMessage(__LINE__, __FILE__, zlog::ERROR)
#define ZLOG_FATAL() zlog::details::LogMessage(__LINE__, __FILE__, zlog::FATAL)
namespace zlog {

void Init() {}

}  // namespace zlog
#endif  // ZLOG_ZLOG_H_