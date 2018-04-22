#include "WindowInterface.h"

#include <string>

#include "Settings.h"

void WindowInterface::update_kps()
{
    std::string help_str = std::to_string(static_cast<int>(kps)) + "    ";
    kps_str = help_str.c_str();

    std::string help_str_2 = std::to_string(static_cast<int>(max_kps)) + "    ";
    max_kps_str = help_str_2.c_str();

    if (Settings::getInstance()->TotalKeysOn())
    {
        std::string help_str_3 = std::to_string(static_cast<int>(total_keys)) + "    ";
        total_keys_str = help_str_3.c_str();
    }

    //RedrawWindow(*window_ptr, NULL, NULL, RDW_INVALIDATE);
}

void WindowInterface::toggle_window_on_top( bool set_on_top )
{
    if (set_on_top)
    {
        // Make window position always on top
        SetWindowPos(*window_ptr, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
    else
    {
        // Make window position normal
        SetWindowPos(*window_ptr, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
    }
}

void WindowInterface::toggle_window_borders(bool set_border)
{
    if (set_border)
    {
        // Give borders to window
        SetWindowLongPtr(*window_ptr,GWL_STYLE,WS_OVERLAPPEDWINDOW);
        ShowWindow(*window_ptr, SW_SHOW);
    }
    else
    {
        // Remove borders from window
        SetWindowLongPtr(*window_ptr,GWL_STYLE,WS_BORDER);
        ShowWindow(*window_ptr, SW_SHOW);
    }
}

void WindowInterface::setWindow_ptr(HWND* hwnd)
{
    window_ptr = hwnd;
}

HWND* WindowInterface::getWindow_ptr()
{
    return window_ptr;
}

