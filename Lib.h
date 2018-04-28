#ifndef LIB_H_INCLUDED
#define LIB_H_INCLUDED

#include <string>

namespace Lib
{
    void SysDateTime(std::string &str);
    void SysTime(std::string &str);
    void SysTimeStamp(std::string &str);
    int SysMilliSeconds();
    void PrintTimeStamp();
}

#endif // LIB_H_INCLUDED
