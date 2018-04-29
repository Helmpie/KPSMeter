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
        while(getline(file_ini,line))
        {
            if(line[0]!='/')
            {
                size_t pos = line.find(" = ");

                std::pair<std::string, std::string> val;
                val.first = line.substr(0, pos);
                val.second = line.substr(pos+3);

                SetReadValue(val);
            }
        }
    }
    else
    {
        std::cout << "Failed to open config";
    }

    file_ini.close();
}

void Settings::SetReadValue(std::pair<std::string, std::string> val)
{
    std::cout << val.first << " " << val.second << std::endl;

    if (val.first == "graph_update_rate")
        graph_update_rate = std::atoi((val.second).c_str());
    else if (val.first == "graph_precision")
        graph_precision = std::atoi((val.second).c_str());
    else if (val.first ==  "graph_width")
        graph_width = std::atoi((val.second).c_str());
    else if (val.first ==  "graph_height")
        graph_height = std::atoi((val.second).c_str());
    else if (val.first ==  "graph_top")
        graph_top = std::atoi((val.second).c_str());
    else if (val.first ==  "generate_csv")
        b_generate_csv = std::atoi((val.second).c_str());
    else if (val.first ==  "csv_update_rate")
        csv_update_rate = std::atoi((val.second).c_str());
    else if (val.first ==  "calc_queue_size")
        calc_queue_size = std::atoi((val.second).c_str());
    else if (val.first == "calc_update_rate")
        calc_update_rate = std::atoi((val.second).c_str());
    else if (val.first ==  "calc_win_update_rate")
        calc_win_update_rate  = std::atoi((val.second).c_str());
    else if (val.first == "share_update_rate")
        share_update_rate = std::atoi((val.second).c_str());
    else if (val.first == "user")
        user = val.second;
    else
        std::cout << "Parse error!";
}

void Settings::ToggleKPSAlwaysOnTop()
{
    b_kps_always_on_top = !b_kps_always_on_top;
}

bool Settings::KPSWindowIsAOT()
{
    return b_kps_always_on_top;
}

void Settings::ToggleKPSWindowBorders()
{
    b_kps_window_has_borders = !b_kps_window_has_borders;
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

void Settings::ToggleShareData()
{
    b_share_data = !b_share_data;
}

bool Settings::ShareDataOn()
{
    return b_share_data;
}

short Settings::getShareUpdateRate()
{
    return share_update_rate;
}

void Settings::setCalcUpdateRate(short rate)
{
    calc_update_rate = rate;
}

short Settings::getCalcQueueSize()
{
    return calc_queue_size;
}

short Settings::getCalcUpdateRate()
{
    return calc_update_rate;
}

short Settings::getCalcWinUpdateRate()
{
    return calc_win_update_rate;
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

std::string Settings::getUser()
{
    return user;
}
