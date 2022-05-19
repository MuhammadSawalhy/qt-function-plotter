#ifndef PLOT_SETTINGS_H
#define PLOT_SETTINGS_H

#include <iostream>

struct PlotSettings
{
    double minX;
    double maxX;
    std::string function;
};

extern PlotSettings plotSettings;

/**
 * @brief update the plotting settings which will be used to plot with QCustomPlot
 * @param settings the new settings
 * @return error message if the new settings are invalid
 */
std::string updatePlotSettings(PlotSettings settings);

std::string validateFunction(const char *function);

#endif // PLOT_SETTINGS_H
