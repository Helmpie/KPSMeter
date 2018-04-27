#ifndef WINAPI_H_INCLUDED
#define WINAPI_H_INCLUDED

#include "windows.h"

const char g_szClassName1[] = "myWindowClass1";
const char g_szClassName2[] = "myWindowClass2";

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

namespace WinAPI
{
    bool MakeWindow(WNDCLASSEX& wc,
                    HWND& hwnd,
                    MSG& Msg,
                    HINSTANCE& hInstance,
                    windowInformation& wi);
}

#endif // WINAPI_H_INCLUDED
