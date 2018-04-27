#ifndef WEB_H_INCLUDED
#define WEB_H_INCLUDED

#include "Inet.h"

class Web
{
    public:
        Web();
        ~Web();

        bool OpenConnect();
        bool OpenConnect(const std::string& host);
        bool Update(const std::string& data = "0");
        void Close();

    private:
        void ReadResponse();
        void Failure();

        iNet internet;
        bool connected;
};


#endif // WEB_H_INCLUDED
