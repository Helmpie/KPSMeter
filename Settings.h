#ifndef SETTINGS_H_INCLUDED
#define SETTINGS_H_INCLUDED

#include "WindowInterface.h"

class Settings : public WindowInterface
{
    private:
        static Settings* instance;

        Settings();
        ~Settings();

        bool b_always_on_top = false;
        bool b_window_has_borders = true;
        bool b_total_keys_on = true;
        bool b_precision_mode = true;

        bool b_generate_csv = false;

        short graph_update_rate;// = 350; // in milliseconds
        short graph_precision;// = 150;
        short graph_width;// = 400;
        short graph_height;// = 225;
        short graph_top;// = 65;

        void ReadSettings();

    public:
        static Settings* getInstance();

        // Window always on top
        void ToggleAlwaysOnTop();
        bool WindowIsAOT();

        // Borderless window
        void ToggleWindowBorders();
        bool WindowHasBorders();

        // Precision mode
        void TogglePrecisionMode();
        bool PrecisionModeOn();

        // Total keys
        void ToggleTotalKeys();
        bool TotalKeysOn();

        void ToggleGenerateCSV();
        bool getGenerateCSV();

        short getGraphPrecision();
        short getGraphWidth();
        short getGraphHeight();
        short getGraphTop();
        short getGraphUpdateRate();
};

#endif // SETTINGS_H_INCLUDED
