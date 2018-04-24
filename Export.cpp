#include "Export.h"
#include <iostream>

Export::Export(const std::string& filename)
{
    file.open(filename);
    file << "\n0";
}

Export::~Export()
{
    file.close();
}

void Export::WriteToCSV(const std::string& data)
{
    file << ",";
    file << data;
}
