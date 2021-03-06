#include "Lib.h"

#include <chrono>
#include <sys/time.h>
#include <sstream>
#include <iostream>

void Lib::Time::SysDateTime(std::string &str)
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    str = std::ctime(&time);
    str.pop_back();
}

void Lib::Time::SysTime(std::string &str)
{
    std::time_t rawtime;
    struct tm* timeinfo;
    char buffer[9];

    time (&rawtime);
    timeinfo = localtime (&rawtime);

    strftime (buffer,80,"%H:%M:%S",timeinfo);

    str = buffer;
}

void Lib::Time::SysTimeStamp(std::string& str)
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    int milli = curTime.tv_usec / 1000;

    char buffer[4] = "";
    sprintf(buffer, ".%d", milli);

    Lib::Time::SysTime(str);
    str += buffer;
}

int Lib::Time::SysMilliSeconds()
{
    timeval curTime;
    gettimeofday(&curTime, NULL);
    return curTime.tv_usec / 1000;
}

void Lib::Time::PrintTimeStamp()
{
    std::string str;
    Lib::Time::SysTimeStamp(str);
    std::cout << str << std::endl;
}
