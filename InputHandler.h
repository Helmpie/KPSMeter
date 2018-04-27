#ifndef INPUTHANDLER_H_INCLUDED
#define INPUTHANDLER_H_INCLUDED

#include <windows.h>
#include <cstdint>
#include <deque>
#include <string>
#include <sstream>

#include "WindowInterface.h"
#include "Settings.h"

//static const int16_t deque_size = Settings::getInstance()->getCalcPrecision();//14;
static const int16_t deque_size = 14;
//static const float deque_div = ((float)deque_size)/10;

class InputHandler
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

        // String conversion
        std::string getKpsStr();
        std::string getMaxKpsStr();
        std::string getTotalKpsStr();

    private:
        float kps = 0; // result of calculation
        float max_kps = 0; // highest keys per second
        int total_keys = 0;

        int16_t keycount = 0; // number of key-presses registered by keydown();
        std::deque<unsigned char> key_que; // storage for Precision Mode;

        short deque_size;
        float deque_div;
};

#endif // INPUTHANDLER_H_INCLUDED
