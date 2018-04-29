#include "DrawFunctions.h"

#include <windows.h>
#include <Gdiplus.h>
#include <string>
#include <deque>
#include <iostream>

#include "Constants.h"
#include "Settings.h"

void Draw::text(PAINTSTRUCT &ps,
                HDC &hdc,
                const COLORREF &text_color,
                const COLORREF &back_color,
                const HFONT &hFont,
                short top_x,
                short top_y,
                short bot_x,
                short bot_y,
                std::string &str)
{
    // Set font and text color
    SetTextColor(hdc, text_color);
    SelectObject(hdc, hFont);

    // Create rectangle
    RECT rc;
    SetBkColor(hdc, back_color);

    // Set coordinates
    ::SetRect(&rc,top_x,top_y,bot_x,bot_y);

    // Fill in text
    ::DrawText(hdc,str.c_str(),-1,&rc,DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
}

void Draw::text(PAINTSTRUCT &ps,
                HDC &hdc,
                const COLORREF &text_color,
                const COLORREF &back_color,
                const HFONT &hFont,
                short top_x,
                short top_y,
                short bot_x,
                short bot_y,
                const char* str)
{
    // Set font and text color
    SetTextColor(hdc, text_color);
    SelectObject(hdc, hFont);

    // Create rectangle
    RECT rc;
    SetBkColor(hdc, back_color);

    // Set coordinates
    ::SetRect(&rc,top_x,top_y,bot_x,bot_y);

    // Fill in text
    ::DrawText(hdc,str,-1,&rc,DT_LEFT | DT_EXTERNALLEADING | DT_WORDBREAK);
}

void Draw::graph(HDC &hdc,
                 const std::deque<short>* dots)
{
    Gdiplus::Graphics graphics(hdc);
    Gdiplus::Pen whitePen(Gdiplus::Color(255, 255, 255, 255), 1);

    for(float i=0; i<dots->size()-1; i++)
    {
        graphics.DrawLine(&whitePen,
                          i*w_factor, // X1
                          height - (*dots)[i]*h_factor, // Y1
                          (i+1)*w_factor, // X2
                          height - (*dots)[i+1]*h_factor); // Y2
    }
}
