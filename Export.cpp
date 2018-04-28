#include "Export.h"

#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>

#include "Settings.h"
#include "Lib.h"

Export::Export()
{

}

Export::~Export()
{
    file.close();
}

void Export::openCSV()
{
    std::string filename;
    Lib::SysDateTime(filename);

    filename += ".csv";
    filename.erase(std::remove(filename.begin(), filename.end(), ':'), filename.end());

    file.open(filename);
    file << "KPS, Timestamps\n";

    total = 0;
}

void Export::closeCSV()
{
    file.close();
}

void Export::UpdateAverage(const float& data)
{
    total += data;
}

void Export::WriteToCSV()
{
    if(file.is_open())
    {
        short average =
            total / (Settings::getInstance()->getCSVUpdateRate() / Settings::getInstance()->getCalcUpdateRate());

        std::string time;
        Lib::SysTime(time);

        file << average;
        file << ",";
        file << time;
        file << "\n";

        total = 0;
    }
}
