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
        int settings[6];
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
    }
    else
    {
        std::cout << "Failed to open config";
    }

    file_ini.close();
}

void Settings::ToggleAlwaysOnTop()
{
    if (!b_always_on_top)
    {
        toggle_window_on_top(true);
        b_always_on_top = true;
    }
    else
    {
        toggle_window_on_top(false);
        b_always_on_top = false;
    }
}

bool Settings::WindowIsAOT()
{
    return b_always_on_top;
}

void Settings::ToggleWindowBorders()
{
    if (!b_window_has_borders)
    {
        toggle_window_borders(true);
        b_window_has_borders = true;
    }
    else
    {
        toggle_window_borders(false);
        b_window_has_borders = false;
    }
}

bool Settings::WindowHasBorders()
{
    return b_window_has_borders;
}

void Settings::TogglePrecisionMode()
{
    if (!b_precision_mode)
    {
        b_precision_mode = true;
    }
    else
    {
        b_precision_mode = false;
    }
}

bool Settings::PrecisionModeOn()
{
    return b_precision_mode;
}

void Settings::ToggleTotalKeys()
{
    if (!b_total_keys_on)
    {
        b_total_keys_on = true;
    }
    else
    {
        b_total_keys_on = false;
    }
}

bool Settings::TotalKeysOn()
{
    return b_total_keys_on;
}

void Settings::ToggleGenerateCSV()
{
    b_generate_csv = !b_generate_csv;
}

bool Settings::getGenerateCSV()
{
    return b_generate_csv;
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
