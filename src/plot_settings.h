#ifndef PLOT_SETTINGS_H
#define PLOT_SETTINGS_H

#include <iostream>

struct PlotSettings {
    double minX;
    double maxX;
    std::string function;
};

extern PlotSettings* plotSettings;

bool updatePlotSettings(PlotSettings *settings);

#endif // PLOT_SETTINGS_H
