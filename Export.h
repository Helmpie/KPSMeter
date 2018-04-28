#ifndef EXPORT_H_INCLUDED
#define EXPORT_H_INCLUDED

#include <string>
#include <fstream>

class Export
{
    public:
        Export();
        ~Export();

        void openCSV();
        void closeCSV();

        void UpdateAverage(const float& data);
        void WriteToCSV();

    private:
        float total = 0;
        float div = 1;
        std::ofstream file;
};

#endif // EXPORT_H_INCLUDED
