#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <Tchar.h>
#include <gdiplus.h>
#include <string>

#include "Constants.h"
#include "WinAPI.h"
#include "Settings.h"
#include "Lib.h"
#include "InputHandler.h"
#include "DrawFunctions.h"
#include "Graph.h"

#ifndef __LITE__
#include "Export.h"
#include "Web.h"
#include "IO.h"
#endif // __LITE__

static InputHandler input;
static Graph graph;
#ifndef __LITE__
static Export csv;
#endif // __LITE__

// Timers
const int KPS_TIMER = 1;
const int GRAPH_TIMER = 2;
const int CALC_TIMER = 3;
const int CSV_TIMER = 4;

// Graph background
static HBITMAP graph_bg = (HBITMAP) LoadImage(0,_T("bg.bmp"),
                                       IMAGE_BITMAP,0,0,
                                       LR_CREATEDIBSECTION|LR_LOADFROMFILE);

// Callback function for main message loop
LRESULT CALLBACK WndProcPrim(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_TIMER:
            switch (wParam)
            {
                case KPS_TIMER:
                    InvalidateRect(hwnd,NULL,FALSE);
                    break;
#ifndef __LITE__
                case CSV_TIMER:
                    if(Settings::getInstance()->getGenerateCSV())
                    {
                        csv.WriteToCSV();
                    }
                    break;
#endif
            }
            break;
        case WM_PAINT:
        {
            /* double buffering code @http://www.robertelder.ca/doublebuffering/ */
            PAINTSTRUCT ps;
            HDC Memhdc;
            HDC hdc;
            HBITMAP Membitmap;
            hdc = BeginPaint(hwnd, &ps);
            Memhdc = CreateCompatibleDC(hdc);
            Membitmap = CreateCompatibleBitmap(hdc, 265, 265);
            SelectObject(Memhdc, Membitmap);

            Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_l,10,5,140,70,kps_txt);
            Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_s,10,70,140,110,max_txt);
            Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_l,130,5,300,70,input.getKpsStr().c_str());
            Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_s,100,70,300,110,input.getMaxKpsStr().c_str());

            if ( Settings::getInstance()->TotalKeysOn() )
            {
                Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_s,10,110,140,150,tot_txt);
                Draw::text(ps,Memhdc,colorWhite,colorBlack,hFont_s,100,110,300,150,input.getTotalKpsStr().c_str());
            }

            BitBlt(hdc, 0, 0,
                   265,
                   265,
                   Memhdc, 0, 0, SRCCOPY);

            DeleteObject(Membitmap);
            DeleteDC    (Memhdc);
            DeleteDC    (hdc);
            EndPaint(hwnd, &ps);

            break;
        }

        case WM_ERASEBKGND:
            return 1;

        case WM_CONTEXTMENU:
        {
            WinAPI::CreateRightClickMenuKPS(hwnd);

            // Send command back to message loop
            PostMessage(hwnd, WM_NULL, 0, 0);

            break;
        }

        case WM_COMMAND:
        {
            // Handle command from right click menu
            WORD command = LOWORD(wParam);

            switch (command)
            {
                case COMM_AOT:
                    Settings::getInstance()->ToggleKPSAlwaysOnTop();
                    Settings::getInstance()->toggle_window_on_top(hwnd, Settings::getInstance()->KPSWindowIsAOT());
                    break;

                case COMM_BORDER:
                    Settings::getInstance()->ToggleKPSWindowBorders();
                    Settings::getInstance()->toggle_window_borders(hwnd, Settings::getInstance()->KPSWindowHasBorders());
                    break;

                case COMM_PREC:
                    Settings::getInstance()->TogglePrecisionMode();
                    break;

                case COMM_TOT:
                    Settings::getInstance()->ToggleTotalKeys();
                    InvalidateRect (hwnd, NULL, true);
                    UpdateWindow (hwnd);
                    break;
#ifndef __LITE__
                case COMM_CSV:
                    if(!Settings::getInstance()->getGenerateCSV())
                    {
                        SetTimer(hwnd, CSV_TIMER, Settings::getInstance()->getCSVUpdateRate(), NULL);
                        csv.openCSV();
                    }
                    else
                    {
                        KillTimer(hwnd, CSV_TIMER);
                        csv.closeCSV();
                    }
                    Settings::getInstance()->ToggleGenerateCSV();
                    break;

                case COMM_SHR:
                    // Kill any existing thread
                    IO::KillThread();

                    if(!Settings::getInstance()->ShareDataOn())
                    {

                        IO::StartThread(&input);
                    }
                    Settings::getInstance()->ToggleShareData();
                    break;
#endif // __LITE__
                case COMM_DEC:
                    Settings::getInstance()->ToggleDecimalPoint();
                    break;

                default:
                    break;
            }

            break;
        }

        /** FOR BORDERLESS WINDOW

        case WM_NCHITTEST:
        {
            if (!settings.WindowHasBorders())
            {
                // Makes window draggable
                LRESULT hit = DefWindowProc(hwnd, msg, wParam, lParam);
                if (hit == HTCLIENT)
                {
                    hit = HTCAPTION;
                }
                return hit;
            }
            break;
        }

        //case WM_NCRBUTTONUP:
        //    std::cout << "check nc" << std::endl;
        //    break;

        **/

        case WM_CLOSE:
            // Stop calculation timer when exiting
            KillTimer(hwnd,KPS_TIMER);

            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
#ifndef __LITE__
            // Kill share thread
            IO::KillThread();
#endif // __LITE__
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

// Callback function for secondary message loop
LRESULT CALLBACK WndProcSec(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch(msg)
    {
        case WM_TIMER:
            graph.addDot(input.getKps());
            InvalidateRect(hwnd, NULL, TRUE);

            break;
        case WM_PAINT:
            {
                /* double buffering code @http://www.robertelder.ca/doublebuffering/ */
                PAINTSTRUCT ps;
                HDC Memhdc;
                HDC hdc;
                HBITMAP Membitmap;
                hdc = BeginPaint(hwnd, &ps);
                Memhdc = CreateCompatibleDC(hdc);
                Membitmap = (HBITMAP) CopyImage(graph_bg, IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE);
                SelectObject(Memhdc, Membitmap);

                //drawing code goes in here
                Draw::graph(Memhdc, graph.getDotPtr());

                BitBlt(hdc, 0, 0,
                       Settings::getInstance()->getGraphWidth(),
                       Settings::getInstance()->getGraphHeight()+7,
                       Memhdc, 0, 0, SRCCOPY);

                DeleteObject(Membitmap);
                DeleteDC    (Memhdc);
                DeleteDC    (hdc);
                EndPaint(hwnd, &ps);
            }
            break;
        case WM_ERASEBKGND:
            return 1;

        case WM_CONTEXTMENU:
            {
                WinAPI::CreateRightClickMenuGraph(hwnd);

                // Send command back to message loop
                PostMessage(hwnd, WM_NULL, 0, 0);

                break;
            }

        case WM_COMMAND:
            {
                // Handle command from right click menu
                WORD command = LOWORD(wParam);

                switch (command)
                {
                    case COMM_AOT:
                        Settings::getInstance()->ToggleGraphAlwaysOnTop();
                        Settings::getInstance()->toggle_window_on_top(hwnd, Settings::getInstance()->GraphWindowIsAOT());
                        break;

                    case COMM_BORDER:
                        Settings::getInstance()->ToggleGraphWindowBorders();
                        Settings::getInstance()->toggle_window_borders(hwnd, Settings::getInstance()->GraphWindowHasBorders());
                        break;

                    default:
                        break;
                }
                break;
            }
        case WM_CLOSE:
            // Stop graph timer when exiting
            KillTimer(hwnd,GRAPH_TIMER);

            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
#ifndef __LITE__
            // Kill share thread
            IO::KillThread();
#endif // __LITE__
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
}

VOID CALLBACK CalcTimerCallback(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
    // Adjust tick rate
    static bool init = true;
    if (init && WinAPI::InitUpdateRate(init)) {}

    if (Settings::getInstance()->PrecisionModeOn())
    {
        input.calculate_kps_prec();
    }
    else
    {
        input.calculate_kps_apr();
    }
#ifndef __LITE__
    if(Settings::getInstance()->getGenerateCSV())
    {
        csv.UpdateAverage(input.getKps());
    }

    if(Settings::getInstance()->ShareDataOn())
    {
        IO::AddKps(input.getKps());
    }
#endif // __LITE__
}

// Callback function for keyboard hook
LRESULT CALLBACK MyKeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION)
    {
        switch (wParam)
        {
            case WM_KEYDOWN:
                KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT*)lParam;

                if ( GetAsyncKeyState(kbdStruct->vkCode) >= 0 )
                {
                    input.keydown();
                }

                // reset max keys per second on '~'
                if ( kbdStruct->vkCode == VK_OEM_3 )
                {
                    input.ResetMaxKps();
                }
                break;
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc, wc2;
    HWND hwnd, hwnd2;
    MSG Msg;

    // Make main window
    windowInformation wi_1(265, 200, g_szClassName1, "KPS", NULL, WndProcPrim);

    if(!WinAPI::MakeWindow(wc, hwnd, Msg, hInstance, wi_1))
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Make graph window
    windowInformation wi_2(Settings::getInstance()->getGraphWidth(),
                           Settings::getInstance()->getGraphHeight()+40,
                           g_szClassName2, "Graph", "bg.bmp", WndProcSec);

    if(!WinAPI::MakeWindow(wc2, hwnd2, Msg, hInstance, wi_2))
    {
        return 0;
    }
    ShowWindow(hwnd2, nCmdShow);
    UpdateWindow(hwnd2);

    // Keyboard hook for registering key-down events while not in focus
    SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyboardProc, 0, 0);

    // Init GDIPlus
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Start timers
    SetTimer(hwnd, KPS_TIMER, Settings::getInstance()->getCalcWinUpdateRate(), NULL);
    SetTimer(hwnd2, GRAPH_TIMER, Settings::getInstance()->getGraphUpdateRate(), NULL);
    SetTimer(hwnd, CALC_TIMER, Settings::getInstance()->getCalcUpdateRate(), CalcTimerCallback);

    //  Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
