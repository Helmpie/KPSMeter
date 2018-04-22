#include "InputHandler.h"

#include "Settings.h"

InputHandler::InputHandler()
{
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
    kps = kps*0.90;
    kps += keycount;
    keycount = 0;

    if (kps > max_kps) {max_kps=kps;}

    update_kps();
}

void InputHandler::calculate_kps_prec()
{
    kps = 0;
    key_que.pop_front();
    key_que.push_back(keycount);
    for (int i=0;i<deque_size;i++) { kps += key_que[i]; }
    //std::cout << key_que.size() << std::endl;
    kps = kps/deque_div;

    keycount = 0;

    if (kps > max_kps) {max_kps=kps;}

    update_kps();
}

int16_t InputHandler::getKeycount()
{
    return keycount;
}

float InputHandler::getKps()
{
    return kps;
}
