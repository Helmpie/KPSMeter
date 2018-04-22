#ifndef WINDOWINTERFACE_H_INCLUDED
#define WINDOWINTERFACE_H_INCLUDED

#include <windows.h>

// Interface class which holds calculation results
// Can be accessed by registered window
class WindowInterface
{
    public:
        // Settings menu callbacks
        void toggle_window_on_top( bool set_on_top );
        void toggle_window_borders( bool set_border );

        // Data access
        void setKPSWindow_ptr(HWND* hwnd);
        HWND* getKPSWindow_ptr();

        void setGraphWindow_ptr(HWND* hwnd);
        HWND* getGraphWindow_ptr();

    private:
        // registered windows
        HWND* kps_window_ptr;
        HWND* graph_window_ptr;
};

#endif // WINDOWINTERFACE_H_INCLUDED
