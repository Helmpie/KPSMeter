#ifndef DRAWFUNCTIONS_H_INCLUDED
#define DRAWFUNCTIONS_H_INCLUDED

#include <windows.h>
#include <string>
#include <deque>
#include <gdiplus.h>

// Calling any function in this namespace requires an HDC handle that has been opened with BeginPaint()
// Functions do not close or release the provided handles.
namespace Draw
{
    //@brief        Wrapper function for drawing text in a rectangle using windows.h
    //
    //@param[in] PAINTSTRUCT &ps,               calling this function.
    //@param[in] HDC &hdc,
    //@param[in] const COLORREF &text_color,    Color of the text
    //@param[in] const COLORREF &back_color,    Color of the rectangle background
    //@param[in] const HFONT &hFont             Typeface of the text
    //@param[in] short top_x,                   Coordinates of the rectangle top left and bottom right
    //@param[in] short top_y,
    //@param[in] short bot_x,
    //@param[in] short bot_y,
    //@param[in] std::string &str)              Text to write in the rectangle
    void text(PAINTSTRUCT &ps,
              HDC &hdc,
              const COLORREF &text_color,
              const COLORREF &back_color,
              const HFONT &hFont,
              const short top_x,
              const short top_y,
              const short bot_x,
              const short bot_y,
              std::string &str);

    //@brief        Wrapper function for drawing text in a rectangle using windows.h
    //
    //@param[in] PAINTSTRUCT &ps,               calling this function.
    //@param[in] HDC &hdc,
    //@param[in] const COLORREF &text_color,    Color of the text
    //@param[in] const COLORREF &back_color,    Color of the rectangle background
    //@param[in] const HFONT &hFont             Typeface of the text
    //@param[in] short top_x,                   Coordinates of the rectangle top left and bottom right
    //@param[in] short top_y,
    //@param[in] short bot_x,
    //@param[in] short bot_y,
    //@param[in] std::string &str)              Text to write in the rectangle
    void text(PAINTSTRUCT &ps,
              HDC &hdc,
              const COLORREF &text_color,
              const COLORREF &back_color,
              const HFONT &hFont,
              const short top_x,
              const short top_y,
              const short bot_x,
              const short bot_y,
              const char* str);

    void graph(HDC &hdc,
               const std::deque<short>* dots);
}

#endif // DRAWFUNCTIONS_H_INCLUDED
