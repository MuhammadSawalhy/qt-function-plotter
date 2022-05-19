#include "./plot_settings.h"

PlotSettings* plotSettings;

bool updatePlotSettings(PlotSettings *newSettings) {
    delete plotSettings; // TODO: learn more about delete statement
    plotSettings = newSettings;
    return true;
}
