#include "InetError.h"

Error::Error(HINTERNET &handle, std::string msg)
: errorMsg(msg)
{
    writeErrConsole();
    closeConnection(handle);
}

Error::Error(HINTERNET &handle, std::string msg, std::string param_1)
: errorMsg(msg), param_1(param_1 = "")
{
    writeErrConsole();
    closeConnection(handle);
}

Error::Error(std::string msg)
: errorMsg(msg)
{
    writeErrConsole();
}

Error::Error(std::string msg, std::string param_1)
: errorMsg(msg), param_1(param_1 = "")
{
    writeErrConsole();
}

Error::~Error()
{

}

void Error::writeErrConsole()
{
    std::cout << errorMsg << " "
              << param_1 << " "
              << std::endl;
}

void Error::closeConnection(HINTERNET &handle)
{
    DWORD ErrorNum = GetLastError();
    std::cout << "Error No: " << ErrorNum << std::endl;

    InternetCloseHandle(handle);
}
