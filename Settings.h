#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "WindowInterface.h"

class Settings : public WindowInterface
{
    private:
        static Settings* instance;

        Settings();
        ~Settings();

        // KPS window settings
        bool b_kps_always_on_top = false;
        bool b_kps_window_has_borders = true;
        bool b_kps_total_keys_on = true;
        bool b_kps_precision_mode = true;
        bool b_kps_decimal_point = false;

        // Graph window settings
        bool b_graph_always_on_top = false;
        bool b_graph_window_has_borders = true;

        // Calculation settings
        short calc_queue_size;// = 14;
        short calc_update_rate;// = 100;

        // CSV settings
        bool b_generate_csv = false;
        short csv_update_rate;

        // Graph settings
        short graph_update_rate;// = 350; // in milliseconds
        short graph_precision;// = 150;
        short graph_width;// = 400;
        short graph_height;// = 225;
        short graph_top;// = 65;

        void ReadSettings();

    public:
        static Settings* getInstance();

        // Window always on top
        void ToggleKPSAlwaysOnTop();
        bool KPSWindowIsAOT();

        void ToggleGraphAlwaysOnTop();
        bool GraphWindowIsAOT();

        // Borderless window
        void ToggleKPSWindowBorders();
        bool KPSWindowHasBorders();

        void ToggleGraphWindowBorders();
        bool GraphWindowHasBorders();

        // Precision mode
        void TogglePrecisionMode();
        bool PrecisionModeOn();

        // Total keys
        void ToggleTotalKeys();
        bool TotalKeysOn();

        void ToggleDecimalPoint();
        bool DecimalPointOn();

        void ToggleGenerateCSV();
        bool getGenerateCSV();

        short getCSVUpdateRate();

        short getCalcQueueSize();
        short getCalcUpdateRate();

        short getGraphPrecision();
        short getGraphWidth();
        short getGraphHeight();
        short getGraphTop();
        short getGraphUpdateRate();
};

#endif // SETTINGS_H_INCLUDED
