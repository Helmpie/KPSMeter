#include "Inet.h"

//CONSTRUCTOR AND DESTRUCTOR
iNet::iNet()
{
    openConnection();
}

iNet::~iNet()
{

}

//OPEN HINTERNET CONNECTION
bool iNet::openConnection()
{
    connect = InternetOpen("Internet",INTERNET_OPEN_TYPE_PRECONFIG,NULL, NULL, 0);

    if(!connect)
    {
        Error("Failed to establish connection");
        return false;
    }
    return true;
}

//OPEN HTTP SESSION
bool iNet::openHttpSession(LPCTSTR url)
{
    httpSession = InternetConnect(connect, url, INTERNET_DEFAULT_HTTP_PORT,
                                  NULL, NULL, INTERNET_SERVICE_HTTP, 0, 0);

    if ( !httpSession )
    {
        Error(connect, "Failed to open HTTP session");
        return false;
    }
    return true;
}

//OPEN HTTP REQUEST
bool iNet::openHttpGETRequest(LPCSTR obj)
{
    OpenHttp = HttpOpenRequest(httpSession, "GET", obj, "HTTP/1.1", 0, 0,
                               INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);

    if ( !OpenHttp )
    {
        Error(httpSession, "Failed to open HTTP request of ", obj);
        return false;
    }
    return true;
}

bool iNet::openHttpPOSTRequest(LPCSTR obj)
{
    OpenHttp = HttpOpenRequest(httpSession, "POST", obj, "HTTP/1.1", 0, 0,
                               INTERNET_FLAG_RELOAD | INTERNET_FLAG_EXISTING_CONNECT, 0);

    if ( !OpenHttp )
    {
        Error(httpSession, "Failed to open HTTP request of ", std::string(obj));
        return false;
    }
    return true;
}

//SEND HTTP REQUEST
bool iNet::sendHttpRequest()
{
    if ( !HttpSendRequest(OpenHttp, NULL, 0, NULL, 0) )
    {
        Error(OpenHttp, "Failed to send HTTP request");
        return false;
    }
    return true;
}

bool iNet::addHttpRequestHeader(LPCTSTR header)
{
    if ( !HttpAddRequestHeaders(OpenHttp, header, -1L, 0) )
    {
        Error(OpenHttp, "Failed to add HTTP request header");
        return false;
    }
    return true;
}

bool iNet::queryHttpRequest()
{
    return true;
}

//CLOSE CONNECTIONS
bool iNet::closeConnection()
{
    if( !InternetCloseHandle(connect) )
    {
        return false;
    }
    return true;
}

bool iNet::closeHttpSession()
{
    if( !InternetCloseHandle(httpSession) )
    {
        return false;
    }
    return true;
}

bool iNet::closeHttpRequest()
{
    if( !InternetCloseHandle(OpenHttp) )
    {
        return false;
    }
    return true;
}

HINTERNET iNet::gethttpSession()
{
    return httpSession;
}

HINTERNET iNet::getOpenHttp()
{
    return OpenHttp;
}

HINTERNET iNet::getConnect()
{
    return connect;
}
