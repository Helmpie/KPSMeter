#include "InputHandler.h"

#include "Settings.h"

#include <iomanip>
#include <iostream>
#include <cmath>

InputHandler::InputHandler()
{
    deque_size = Settings::getInstance()->getCalcQueueSize();
    deque_div = (float)deque_size / (1000/(float)Settings::getInstance()->getCalcUpdateRate());
    appr_div = (float)(1000-Settings::getInstance()->getCalcUpdateRate()) / 1000;

    // init key_que
    for (int i=0;i<deque_size;i++) { key_que.push_back(0); }
}

InputHandler::~InputHandler()
{

}

void InputHandler::keydown()
{
    keycount++;
    total_keys++;
}

void InputHandler::ResetMaxKps()
{
    max_kps = 0;
    kps = -1;

    if ( Settings::getInstance()->PrecisionModeOn() )
    {
        for (int i=0;i<deque_size;i++) { key_que[i] = 0; }
    }
}

void InputHandler::calculate_kps_apr()
{
    kps = kps*appr_div;
    kps += keycount;
    keycount = 0;

    if (kps > max_kps) {max_kps=kps;}
}

void InputHandler::calculate_kps_prec()
{
    kps = 0;
    key_que.pop_back();
    key_que.push_front(keycount);

    for (int i=0;i<deque_size;i++)
    {
        kps += key_que[i];
    }

    kps = kps/deque_div;

    keycount = 0;

    if (kps > max_kps)
    {
        max_kps=kps;
    }
}

int16_t InputHandler::getKeycount()
{
    return keycount;
}

float InputHandler::getKps()
{
    return kps;
}

std::string InputHandler::getKpsStr()
{
    if(Settings::getInstance()->DecimalPointOn())
    {
        std::stringstream ss;
        ss << std::fixed << std::setprecision(1) << kps;
        return ss.str();
    }
    else
    {
        return std::to_string((int)ceil(kps));
    }
}

std::string InputHandler::getMaxKpsStr()
{
    return std::to_string((int)ceil(max_kps));
}

std::string InputHandler::getTotalKpsStr()
{
    return std::to_string(total_keys);
}
