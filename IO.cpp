#include "IO.h"

#include <thread>
#include <mutex>
#include <condition_variable>
#include <iostream>
#include <windows.h>
#include <string>

#include "Web.h"
#include "InputHandler.h"
#include "Settings.h"

static std::thread web_io;
static InputHandler* input_ptr;

static int total_kps;
static int web_div = Settings::getInstance()->getShareUpdateRate() / Settings::getInstance()->getCalcUpdateRate();

bool go = true;
bool active = false;

static void ShareData()
{
    Web web;
    web.OpenConnect();

    while(go)
    {
        //go = web.Update(std::to_string((int)input_ptr->getKps()));
        go = web.Update( std::to_string( (total_kps / web_div) ) );
        total_kps = 0;
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

void IO::AddKps(float kps)
{
    total_kps += kps;
}
