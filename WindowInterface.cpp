#include "WindowInterface.h"

#include <string>

#include "Settings.h"

void WindowInterface::toggle_window_on_top( HWND &hwnd, bool set_on_top )
{
    if (set_on_top)
    {
        // Make window position always on top
        SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        // Make window position normal
        SetWindowPos(hwnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

void WindowInterface::toggle_window_borders( HWND &hwnd, bool set_border )
{
    if (set_border)
    {
        // Give borders to window
        SetWindowLongPtr(hwnd,GWL_STYLE,WS_OVERLAPPEDWINDOW);
        ShowWindow(hwnd, SW_SHOW);
    }
    else
    {
        // Remove borders from window
        SetWindowLongPtr(hwnd,GWL_STYLE,WS_BORDER);
        ShowWindow(hwnd, SW_SHOW);
    }
}
