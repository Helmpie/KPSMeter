#ifndef WINDOWINTERFACE_H_INCLUDED
#define WINDOWINTERFACE_H_INCLUDED

#include <windows.h>

// This class has no reason to exist
class WindowInterface
{
    public:
        // Settings menu callbacks
        void toggle_window_on_top( HWND &hwnd, bool set_on_top );
        void toggle_window_borders( HWND &hwnd, bool set_border );

    private:
};

#endif // WINDOWINTERFACE_H_INCLUDED
