#include "IO.h"

#include <thread>
#include <iostream>
#include <windows.h>
#include <string>

#include "Web.h"
#include "InputHandler.h"

static std::thread web_io;
static InputHandler* input_ptr;
bool go = true;
bool active = false;

static void ShareData()
{
    Web web;
    web.OpenConnect();

    while(go)
    {
        go = web.Update(std::to_string(input_ptr->getKps()));
        Sleep(Settings::getInstance()->getShareUpdateRate());
    }

    web.Close();
}

void IO::StartThread(InputHandler* input)
{
    active = true;
    go = true;
    input_ptr = input;
    web_io = std::thread(ShareData);
}

void IO::KillThread()
{
    if(active)
    {
        active = false;
        go = false;
        web_io.join();
    }
}
