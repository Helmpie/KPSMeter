#include "Web.h"

#include <sstream>
#include <string>

#include "Inet.h"
#include "Lib.h"
#include "Settings.h"
#include "IO.h"

Web::Web()
{
    /* Test code...

    if ( internet.openHttpSession("ptsv2.com") )
    {
        connected = true;
    }

    //internet.openHttpSession("httpbin.org");

    //internet.openHttpGETRequest("get");
    //internet.openHttpPOSTRequest("post");
    //internet.openHttpPOSTRequest("/t/nqfe4-1524857838/post");

    //internet.addHttpRequestHeader("\"data\":\"test\"");

    //internet.sendHttpRequest();

    */
}

Web::~Web()
{
    Close();
}

bool Web::OpenConnect()
{
    if ( internet.openHttpSession("kpsmeter.hylcos.nl") )
    {
        connected = true;
        return true;
    }
    else
    {
        return false;
    }
}

bool Web::OpenConnect(const std::string& host)
{
    if ( internet.openHttpSession(host.c_str()) )
    {
        connected = true;
        return true;
    }
    else
    {
        return false;
    }
}

void Web::Close()
{
    connected = false;

    internet.closeHttpRequest();
    internet.closeHttpSession();
    internet.closeConnection();
}

bool Web::Update(const std::string& data)
{
    if(connected)
    {
        std::string time;
        Lib::SysTime(time);

        std::stringstream JSON;
        JSON << "{"
             << "\"user\":\""
             << Settings::getInstance()->getUser()
             << "\",\"data\":\""
             << data
             << "\"}";


        std::cout << JSON.str() << " ";

        //std::string header = "\"data\":\"" + JSON.str() + "\"";
        if ( !( internet.openHttpPOSTRequest("/newdata.php") &&
                internet.sendHttpPOSTRequest(JSON.str()) ) )
        {
            Failure();
            return false;
        }

        //ReadResponse();

        internet.closeHttpRequest();
    }
    else
    {
        std::cout << "No active connection..." << std::endl;
    }

    return true;
}

void Web::ReadResponse()
{
    HINTERNET openHttp = internet.getOpenHttp();

    BYTE DataReceived;
    DWORD NumberOfBytesRead;

    while(InternetReadFile(openHttp, &DataReceived, 1, &NumberOfBytesRead) && NumberOfBytesRead )
    {
        std::cout << DataReceived;
    }
}

void Web::Failure()
{
    std::cout << "Failure during Http request, disconnecting..." << std::endl;

    Settings::getInstance()->ToggleShareData();
    Close();
}
