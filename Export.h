#ifndef EXPORT_H_INCLUDED
#define EXPORT_H_INCLUDED

#include <string>
#include <fstream>

class Export
{
    public:
        Export(const std::string& file);
        ~Export();

        void WriteToCSV(const std::string& data);

    private:
        std::ofstream file;
};

#endif // EXPORT_H_INCLUDED
