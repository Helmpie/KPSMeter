#include "Lib.h"

#include <chrono>
#include <sstream>
#include <iostream>

void Lib::SysDateTime(std::string &str)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    str = std::ctime(&time);
    str.pop_back();
}

void Lib::SysTime(std::string &str)
{
    std::time_t rawtime;
    struct tm* timeinfo;
    char buffer[9];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%H-%M-%S",timeinfo);

    str = buffer;
}
