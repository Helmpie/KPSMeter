#include "Settings.h"
#include "WindowInterface.h"
#include <iostream>
#include <fstream>
#include <string>

Settings* Settings::instance = 0;

Settings* Settings::getInstance()
{
    if (instance == 0)
    {
        instance = new Settings();
    }

    return instance;
}

Settings::Settings()
{
    ReadSettings();
}

Settings::~Settings()
{

}

void Settings::ReadSettings()
{
    std::string line;
    std::ifstream file_ini("config.txt");
    if(file_ini.is_open())
    {
        int i=0;
        int settings[9];
        while(getline(file_ini,line))
        {
            if(line[0]!='/')
            {
                size_t pos = line.find("= ")+2;
                settings[i] = std::atoi(line.substr(pos).c_str());
                i++;
            }
        }

        graph_update_rate = settings[0];
        graph_precision = settings[1];
        graph_width = settings[2];
        graph_height = settings[3];
        graph_top = settings[4];
        b_generate_csv = settings[5];
        csv_update_rate = settings[6];
        calc_queue_size = settings[7];
        calc_update_rate = settings[8];

    }
    else
    {
        std::cout << "Failed to open config";
    }

    file_ini.close();
}

void Settings::ToggleKPSAlwaysOnTop()
{
    b_kps_always_on_top = !b_kps_always_on_top;
    /*
    if (!b_kps_always_on_top)
    {
        toggle_window_on_top(true);
        b_kps_always_on_top = true;
    }
    else
    {
        toggle_window_on_top(false);
        b_kps_always_on_top = false;
    }
    */
}

bool Settings::KPSWindowIsAOT()
{
    return b_kps_always_on_top;
}

void Settings::ToggleKPSWindowBorders()
{
    b_kps_window_has_borders = !b_kps_window_has_borders;
    /*
    if (!b_kps_window_has_borders)
    {
        toggle_window_borders(true);
        b_kps_window_has_borders = true;
    }
    else
    {
        toggle_window_borders(false);
        b_kps_window_has_borders = false;
    }
    */
}

bool Settings::KPSWindowHasBorders()
{
    return b_kps_window_has_borders;
}

void Settings::ToggleGraphAlwaysOnTop()
{
    b_graph_always_on_top = !b_graph_always_on_top;
}

bool Settings::GraphWindowIsAOT()
{
    return b_graph_always_on_top;
}

void Settings::ToggleGraphWindowBorders()
{
    b_graph_window_has_borders = !b_graph_window_has_borders;
}

bool Settings::GraphWindowHasBorders()
{
    return b_graph_window_has_borders;
}

void Settings::TogglePrecisionMode()
{
    b_kps_precision_mode = !b_kps_precision_mode;
}

bool Settings::PrecisionModeOn()
{
    return b_kps_precision_mode;
}

void Settings::ToggleTotalKeys()
{
    b_kps_total_keys_on = !b_kps_total_keys_on;
}

bool Settings::TotalKeysOn()
{
    return b_kps_total_keys_on;
}

void Settings::ToggleDecimalPoint()
{
    b_kps_decimal_point = !b_kps_decimal_point;
}

bool Settings::DecimalPointOn()
{
    return b_kps_decimal_point;
}

void Settings::ToggleGenerateCSV()
{
    b_generate_csv = !b_generate_csv;
}

bool Settings::getGenerateCSV()
{
    return b_generate_csv;
}

short Settings::getCSVUpdateRate()
{
    return csv_update_rate;
}

short Settings::getCalcQueueSize()
{
    return calc_queue_size;
}

short Settings::getCalcUpdateRate()
{
    return calc_update_rate;
}

short Settings::getGraphPrecision()
{
    return graph_precision;
}

short Settings::getGraphWidth()
{
    return graph_width;
}

short Settings::getGraphHeight()
{
    return graph_height;
}

short Settings::getGraphTop()
{
    return graph_top;
}

short Settings::getGraphUpdateRate()
{
    return graph_update_rate;
}
