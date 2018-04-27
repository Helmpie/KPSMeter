#ifndef CONSTANTS_H_INCLUDED
#define CONSTANTS_H_INCLUDED

#include <tchar.h>
#include <windows.h>
#include <gdiplus.h>

// Commands for right click menu;
#define COMM_AOT 1
#define COMM_BORDER 2
#define COMM_PREC 3
#define COMM_TOT 4
#define COMM_CSV 5
#define COMM_SHR 6
#define COMM_DEC 7

// Text drawing constants
extern const COLORREF colorWhite;
extern const COLORREF colorBlack;

extern const HFONT hFont_l;
extern const HFONT hFont_s;

extern const char* kps_txt;
extern const char* max_txt;
extern const char* tot_txt;

// Graph drawing constants
extern const short precision;
extern const short width;
extern const short width_corrected;
extern const short height;
extern const short graph_top;

extern const float w_factor;
extern const float h_factor;

#endif // CONSTANTS_H_INCLUDED
