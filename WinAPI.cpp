#include "WinAPI.h"

#include <Tchar.h>

#include "InputHandler.h"

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
    if(wi.bg == "")
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
