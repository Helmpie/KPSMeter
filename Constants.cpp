#include "Constants.h"
#include "Settings.h"

// Text drawing constants
const COLORREF colorWhite = RGB(255, 255, 255);
const COLORREF colorBlack = RGB(0, 0, 0);

const HFONT hFont_l = CreateFont(70, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Bahnschrift Light"));
const HFONT hFont_s = CreateFont(40, 0, 0, 0, FW_BOLD, 0, 0, 0, DEFAULT_CHARSET, OUT_OUTLINE_PRECIS,
                        CLIP_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_SWISS, _T("Bahnschrift Light"));

const char* kps_txt = "kps: ";
const char* max_txt = "max: ";
const char* tot_txt = "total: ";

// Graph drawing constants
const short precision = Settings::getInstance()->getGraphPrecision();
const short width = Settings::getInstance()->getGraphWidth();
const short width_corrected = width - (width/precision);
const short height = Settings::getInstance()->getGraphHeight()+5;
const short graph_top = Settings::getInstance()->getGraphTop();

const float w_factor = (float)width_corrected/precision;
const float h_factor = (float)height/graph_top;
