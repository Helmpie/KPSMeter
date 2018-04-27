#ifndef INETERROR_H_INCLUDED
#define INETERROR_H_INCLUDED

#include <iostream>
#include <cstring>
#include <stdio.h>
#include <wininet.h>

class Error
{
    public:
        Error(HINTERNET &handle, std::string msg);
        Error(HINTERNET &handle, std::string msg, std::string param_1);
        Error(std::string msg);
        Error(std::string msg, std::string param_1);
        ~Error();

        void writeErrConsole();
        void closeConnection(HINTERNET &handle);

    private:
        std::string errorMsg;
        std::string param_1;
};

#endif // INETERROR_H_INCLUDED
