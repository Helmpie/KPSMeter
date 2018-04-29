#include "WinAPI.h"

#include <Tchar.h>
#include <iostream>

#include "Constants.h"
#include "Settings.h"
#include "Lib.h"

bool WinAPI::MakeWindow(WNDCLASSEX& wc,
                        HWND& hwnd,
                        MSG& Msg,
                        HINSTANCE& hInstance,
                        windowInformation& wi)
{
    // Registering the Window Class
    wc.cbSize        = sizeof(WNDCLASSEX);
    wc.style         = 0;
    wc.lpfnWndProc   = wi.WndProc;
    wc.cbClsExtra    = 0;
    wc.cbWndExtra    = 0;
    wc.hInstance     = hInstance;
    wc.hIcon         = LoadIcon(NULL, IDI_APPLICATION);
    wc.hCursor       = LoadCursor(NULL, IDC_ARROW);
    if(wi.bg == NULL)
    {
        wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    }
    else
    {
        wc.hbrBackground = CreatePatternBrush((HBITMAP) LoadImage(0,_T(wi.bg),
                                          IMAGE_BITMAP,0,0,
                                          LR_CREATEDIBSECTION|LR_LOADFROMFILE));
    }
    //wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));

    wc.lpszMenuName  = NULL;
    wc.lpszClassName = wi.g_szClassName;
    wc.hIconSm       = LoadIcon(NULL, IDI_APPLICATION);

    if(!RegisterClassEx(&wc))
    {
        MessageBox(NULL, "Window Registration Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    // Creating the Window
    hwnd = CreateWindowEx(
        WS_EX_CLIENTEDGE,
        wi.g_szClassName,
        wi.title,
        //WS_OVERLAPPEDWINDOW,
        (WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ),
        CW_USEDEFAULT, CW_USEDEFAULT, wi.width, wi.height,
        NULL, NULL, hInstance, NULL);

    if(hwnd == NULL)
    {
        MessageBox(NULL, "Window Creation Failed!", "Error!",
            MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    return 1;
}

void WinAPI::CreateRightClickMenuKPS(HWND &hwnd)
{
    // Determine cursor position
    POINT p;
    GetCursorPos(&p);

    // Create dropdown list
    HMENU hMenu = CreatePopupMenu();

    // Add buttons
    if ( Settings::getInstance()->KPSWindowIsAOT() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_AOT,_T("Always on top"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_AOT,_T("Always on top"));
    }

    /*if ( Settings::getInstance()->KPSWindowHasBorders() )
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_BORDER,_T("Borderless"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_BORDER,_T("Borderless"));
    }*/

    if ( Settings::getInstance()->PrecisionModeOn() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_PREC,_T("Precision Mode"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_PREC,_T("Precision Mode"));
    }

    if ( Settings::getInstance()->TotalKeysOn() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_TOT,_T("Show Total Keys"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_TOT,_T("Show Total Keys"));
    }
#ifndef __LITE__
    if ( Settings::getInstance()->getGenerateCSV() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_CSV,_T("Generate CSV file"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_CSV,_T("Generate CSV file"));
    }

    if ( Settings::getInstance()->ShareDataOn() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_SHR,_T("Share data"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_SHR,_T("Share data"));
    }
#endif // __LITE__
    if ( Settings::getInstance()->DecimalPointOn() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_DEC,_T("Show decimal point"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_DEC,_T("Show decimal point"));
    }

    // Show menu at mouse position
    TrackPopupMenu( hMenu,
                    TPM_RIGHTBUTTON,
                    p.x,
                    p.y,
                    0,
                    hwnd,
                    NULL);
}

void WinAPI::CreateRightClickMenuGraph(HWND &hwnd)
{
    // Determine cursor position
    POINT p;
    GetCursorPos(&p);

    // Create dropdown list
    HMENU hMenu = CreatePopupMenu();

    // Add buttons
    if ( Settings::getInstance()->GraphWindowIsAOT() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_AOT,_T("Always on top"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_AOT,_T("Always on top"));
    }

    /*if ( Settings::getInstance()->GraphWindowHasBorders() )
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_BORDER,_T("Borderless"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_BORDER,_T("Borderless"));
    }*/

    // Show menu at mouse position
    TrackPopupMenu( hMenu,
                    TPM_RIGHTBUTTON,
                    p.x,
                    p.y,
                    0,
                    hwnd,
                    NULL);
}

// Win32 timers are unreliable at smaller intervals
// Calculate the actual interval and adjust in Settings
bool WinAPI::InitUpdateRate(bool &init)
{
    static short icount = 1;
    static short one = 1001;
    static short two = 1001;

    // Only recalculate after first 10 ticks
    if(icount<10 && ++icount) return true;

    if(one>1000)
        one = Lib::SysMilliSeconds();
    else if (two>1000)
        two = Lib::SysMilliSeconds();
    else
    {
        // New rate equals diff between two ticks
        short rate;
        rate = (two>one) ? two-one : one - two;
        Settings::getInstance()->setCalcUpdateRate(rate);
        init = false;
    }

    return true;
}
