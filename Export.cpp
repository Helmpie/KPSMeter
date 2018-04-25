#include "Export.h"
#include <iostream>
#include <ctime>

Export::Export(const std::string& filename)
{
    file.open(filename);
    file << "KPS, Timestamps\n";
}

Export::~Export()
{
    file.close();
}

void Export::WriteToCSV(const std::string& data)
{
    file << data;
    file << ",";
    file << 0;
    file << "\n";
}
