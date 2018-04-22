#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

#include <windows.h>
#include <cstdint>
#include <deque>

#include "WindowInterface.h"

static const int16_t deque_size = 14;
static const float deque_div = ((float)deque_size)/10;

class InputHandler : public WindowInterface
{
    public:
        // Constructors and destructor
        InputHandler();
        ~InputHandler();

        // Callback for key-press event
        void keydown();

        // Reset max_kps to 0
        void ResetMaxKps();

        // Calculate kps approximately using kps = previous_kps * 0.9
        void calculate_kps_apr();

        // Calculate precise kps using deque
        void calculate_kps_prec();

        // Data access
        int16_t getKeycount();
        float getKps();
        int getTimerInterval();

    private:
        int16_t keycount = 0; // number of key-presses registered by keydown();
        std::deque<unsigned char> key_que; // storage for Precision Mode;
};

#endif // INPUTHANDLER_H_INCLUDED
