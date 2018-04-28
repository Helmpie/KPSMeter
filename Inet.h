#ifndef INET_H_INCLUDED
#define INET_H_INCLUDED

#include <iostream>
#include <cstring>
#include <wininet.h>

#include "InetError.h"

class iNet
{
    public:
        iNet();
        ~iNet();

        bool openConnection();
        bool closeConnection();

        bool openHttpSession(LPCTSTR url);
        bool closeHttpSession();

        bool openHttpGETRequest(LPCSTR url);
        bool openHttpPOSTRequest(LPCSTR url);
        bool sendHttpRequest();
        bool sendHttpPOSTRequest(const std::string& POST);
        bool addHttpRequestHeader(LPCSTR header);
        bool queryHttpRequest();
        bool closeHttpRequest();

        HINTERNET gethttpSession();
        HINTERNET getOpenHttp();
        HINTERNET getConnect();

    private:
        HINTERNET connect;
        HINTERNET httpSession;
        HINTERNET OpenHttp;
};

#endif // INET_H_INCLUDED
