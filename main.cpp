#include <iostream>
#include <unistd.h>
#include "zlog.h"
using namespace std;

int main(int agrc, char** argv)
{
    ZLOG(INFO) << zlog::Color::blue << "hello world";
    ZLOG(DEBUG) << zlog::Color::green << "hello world";
    ZLOG(ERROR) << zlog::Color::yellow << "hello world";
    ZLOG(WARNING) << zlog::Color::white << "hello world";
    ZLOG(FATAL) << zlog::Color::red << "hello world";
    return 0; 
}