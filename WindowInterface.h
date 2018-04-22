#ifndef WINDOWINTERFACE_H_INCLUDED
#define WINDOWINTERFACE_H_INCLUDED

#include <windows.h>

// Interface class which holds calculation results
// Can be accessed by registered window
class WindowInterface
{
    public:
        // Report keys per second to window
        void update_kps();

        // Settings menu callbacks
        void toggle_window_on_top( bool set_on_top );
        void toggle_window_borders( bool set_border );

        // Data access
        void setWindow_ptr(HWND* hwnd);
        HWND* getWindow_ptr();

        // Strings for display in window
        const char* kps_str = "";
        const char* max_kps_str = "";
        const char* total_keys_str = "";

    protected:
        float kps = 0; // result of calculation
        float max_kps = 0; // highest keys per second
        int total_keys = 0;
        HWND* window_ptr;

    private:
         // registered window
};

#endif // WINDOWINTERFACE_H_INCLUDED
