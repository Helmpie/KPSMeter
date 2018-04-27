#include "Lib.h"

#include <chrono>

void Lib::SysTime(std::string &str)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    str = std::ctime(&time);
    str.pop_back();
}
