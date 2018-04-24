#include <iostream>
#include <windows.h>
#include <stdio.h>
#include <Tchar.h>
#include <gdiplus.h>
#include <string>

#include "Settings.h"
#include "InputHandler.h"
#include "DrawFunctions.h"
#include "Graph.h"
#include "Export.h"

static InputHandler input;
static Graph graph;
static Export csv("kps.csv");

const char g_szClassName1[] = "myWindowClass1";
const char g_szClassName2[] = "myWindowClass2";

// Graph background
static HBITMAP graph_bg = (HBITMAP) LoadImage(0,_T("bg.bmp"),
                                              IMAGE_BITMAP,0,0,
                                              LR_CREATEDIBSECTION|LR_LOADFROMFILE);

// Commands for right click menu;
#define COMM_AOT 1
#define COMM_BORDER 2
#define COMM_PREC 3
#define COMM_TOT 4
#define COMM_CSV 5

// Timer ID
const int KPS_TIMER = 1;
const int GRAPH_TIMER = 2;

typedef LRESULT CALLBACK (*callback_ptr)(HWND,UINT,WPARAM,LPARAM);

struct windowInformation
{
    int width;
    int height;
    const char* g_szClassName;
    const char* title;
    const char* bg;
    callback_ptr WndProc;

    windowInformation(int width,
                      int height,
                      const char* g_szClassName,
                      const char* title,
                      const char* bg,
                      callback_ptr WndProc)
    : width(width), height(height), g_szClassName(g_szClassName), title(title), bg(bg), WndProc(WndProc)  {}
};

void CreateRightClickMenu(HWND &hwnd)
{
    // Determine cursor position
    POINT p;
    GetCursorPos(&p);

    // Create dropdown list
    HMENU hMenu = CreatePopupMenu();

    // Add buttons to list

    // Checkbox for window always on top
    if ( Settings::getInstance()->WindowIsAOT() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_AOT,_T("Always on top"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_AOT,_T("Always on top"));
    }

    // Checkbox for borderless window
    if ( Settings::getInstance()->WindowHasBorders() )
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_BORDER,_T("Borderless"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_BORDER,_T("Borderless"));
    }

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

    if ( Settings::getInstance()->getGenerateCSV() )
    {
        ::AppendMenu(hMenu,MF_CHECKED,COMM_CSV,_T("Generate CSV file"));
    }
    else
    {
        ::AppendMenu(hMenu,MF_UNCHECKED,COMM_CSV,_T("Generate CSV file"));
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

// Callback function for main message loop
LRESULT CALLBACK WndProcPrim(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    /* DEBUG */
    //if ( msg!= WM_PAINT ) { std::cout << msg << std::endl; }

    switch(msg)
    {
        case WM_TIMER:
            // Update kps on timer end
            if (Settings::getInstance()->PrecisionModeOn())
            {
                input.calculate_kps_prec();
            }
            else
            {
                input.calculate_kps_apr();
            }

            InvalidateRect(hwnd,NULL,FALSE);
            break;
        case WM_PAINT:
        {
            static const COLORREF colorWhite = RGB(255, 255, 255);
            static const COLORREF colorBlack = RGB(0, 0, 0);

            static const HFONT hFont_l = CreateFont(70, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                           CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Bahnschrift Light"));
            static const HFONT hFont_s = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                                           CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Bahnschrift Light"));

            static const char* kps_txt = "kps: ";
            static const char* max_txt = "max: ";
            static const char* tot_txt = "total: ";

            /* double buffering code @http://www.robertelder.ca/doublebuffering/ */
            PAINTSTRUCT ps;
            HDC Memhdc;
            HDC hdc;
            HBITMAP Membitmap;
            hdc = BeginPaint(hwnd, &ps);
            Memhdc = CreateCompatibleDC(hdc);
            Membitmap = CreateCompatibleBitmap(hdc, 240, 207);
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
                   240,
                   207,
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
            CreateRightClickMenu(hwnd);

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
                    Settings::getInstance()->ToggleAlwaysOnTop();
                    break;

                case COMM_BORDER:
                    Settings::getInstance()->ToggleWindowBorders();
                    break;

                case COMM_PREC:
                    Settings::getInstance()->TogglePrecisionMode();
                    break;

                case COMM_TOT:
                    Settings::getInstance()->ToggleTotalKeys();
                    InvalidateRect (hwnd, NULL, true);
                    UpdateWindow (hwnd);
                    break;

                case COMM_CSV:
                    Settings::getInstance()->ToggleGenerateCSV();
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
            // Update graph on timer end
            graph.addDot(input.getKps());

            if(Settings::getInstance()->getGenerateCSV())
            {
                csv.WriteToCSV(std::to_string((int)input.getKps()));
            }

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
        case WM_CLOSE:
            // Stop graph timer when exiting
            KillTimer(hwnd,GRAPH_TIMER);
            DestroyWindow(hwnd);
            break;
        case WM_DESTROY:
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, msg, wParam, lParam);
    }
    return 0;
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

bool makeWindow(WNDCLASSEX& wc,
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
    //wc.hbrBackground = CreateSolidBrush(RGB(0, 0, 0));
    wc.hbrBackground = CreatePatternBrush((HBITMAP) LoadImage(0,_T(wi.bg),
                                          IMAGE_BITMAP,0,0,
                                          LR_CREATEDIBSECTION|LR_LOADFROMFILE));
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
        WS_OVERLAPPEDWINDOW,
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

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
    LPSTR lpCmdLine, int nCmdShow)
{
    WNDCLASSEX wc, wc2;
    HWND hwnd, hwnd2;
    MSG Msg, Msg2;

    // Make main window
    windowInformation wi_1(240, 200, g_szClassName1, "KPS", "empty.bmp", WndProcPrim);
    if(!makeWindow(wc, hwnd, Msg, hInstance, wi_1))
    {
        return 0;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    // Make graph window
    windowInformation wi_2(Settings::getInstance()->getGraphWidth()+20,
                           Settings::getInstance()->getGraphHeight()+50,
                           g_szClassName2, "Graph", "bg.bmp", WndProcSec);
    if(!makeWindow(wc2, hwnd2, Msg, hInstance, wi_2))
    {
        return 0;
    }
    ShowWindow(hwnd2, nCmdShow);
    UpdateWindow(hwnd2);

    // Keyboard hook for registering key-down events while not in focus
    HHOOK KeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, MyKeyboardProc, 0, 0);

    // Make windows known to Settings
    Settings::getInstance()->setKPSWindow_ptr(&hwnd);
    Settings::getInstance()->setGraphWindow_ptr(&hwnd2);

    // Init GDIPlus
    Gdiplus::GdiplusStartupInput gdiplusStartupInput;
    ULONG_PTR gdiplusToken;
    Gdiplus::GdiplusStartup(&gdiplusToken, &gdiplusStartupInput, NULL);

    // Start timers
    SetTimer(hwnd, KPS_TIMER, 100, NULL);
    SetTimer(hwnd2, GRAPH_TIMER, Settings::getInstance()->getGraphUpdateRate(), NULL);

    //  Message Loop
    while(GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
