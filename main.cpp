#include "zlog.h"
#include <iostream>
#include <thread>
int main(int agrc, char** argv)
{
    zlog::Init();
    ZLOG(INFO) << zlog::Color::blue << "Hello zlog";
    ZLOG(DEBUG) << "Support for int: " << 12456;
    ZLOG(ERROR) << zlog::Color::yellow << "Support for color string: " << "give your some color";
    ZLOG(WARNING) << "23333";
    ZLOG(FATAL) << zlog::Color::red << "easy to use";
    return 0;
}