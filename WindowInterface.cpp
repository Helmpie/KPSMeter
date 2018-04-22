#include "WindowInterface.h"

#include <string>

#include "Settings.h"

void WindowInterface::toggle_window_on_top( bool set_on_top )
{
    if (set_on_top)
    {
        // Make window position always on top
        SetWindowPos(*kps_window_ptr, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        // Make window position normal
        SetWindowPos(*kps_window_ptr, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

void WindowInterface::toggle_window_borders(bool set_border)
{
    if (set_border)
    {
        // Give borders to window
        SetWindowLongPtr(*kps_window_ptr,GWL_STYLE,WS_OVERLAPPEDWINDOW);
        ShowWindow(*kps_window_ptr, SW_SHOW);
    }
    else
    {
        // Remove borders from window
        SetWindowLongPtr(*kps_window_ptr,GWL_STYLE,WS_BORDER);
        ShowWindow(*kps_window_ptr, SW_SHOW);
    }
}

void WindowInterface::setKPSWindow_ptr(HWND* hwnd)
{
    kps_window_ptr = hwnd;
}

HWND* WindowInterface::getKPSWindow_ptr()
{
    return kps_window_ptr;
}

void WindowInterface::setGraphWindow_ptr(HWND* hwnd)
{
    graph_window_ptr = hwnd;
}

HWND* WindowInterface::getGraphWindow_ptr()
{
    return graph_window_ptr;
}
