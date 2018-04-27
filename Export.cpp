#include "Export.h"
#include "Settings.h"
#include <string>
#include <iostream>
#include <ctime>
#include <chrono>
#include <algorithm>

Export::Export()
{

}

Export::~Export()
{
    file.close();
}

void Export::openCSV()
{
    std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
    std::string datetime(std::ctime(&time));
    std::string filename = datetime.erase(datetime.find('\n', 0), 1) + ".csv";
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
        short average = total/((Settings::getInstance()->getCSVUpdateRate()/1000)*(1000/Settings::getInstance()->getCalcUpdateRate()));

        std::time_t time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        std::string datetime(std::ctime(&time));

        file << average;
        file << ",";
        file << datetime;
        //file << "\n";

        total = 0;
    }
}

