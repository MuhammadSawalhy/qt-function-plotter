#include <iostream>
#include <muParser.h>
#include "./plot_settings.h"

PlotSettings* plotSettings;

std::string updatePlotSettings(PlotSettings *newSettings)
{
    std::string errMsg;

    if (newSettings->minX >= newSettings->maxX)
        return "max x should be greater than min x";

    errMsg = validateFunction(newSettings->function.c_str());
    if (!errMsg.empty())
        return errMsg;

    delete plotSettings; // TODO: learn more about delete statement
    plotSettings = newSettings;
    return "";
}

std::string validateFunction(const char *function)
{
    try
    {
        mu::Parser p;
        p.DefineConst("x", 1.111234789);
        p.SetExpr(function);
        p.Eval();
    } catch (mu::Parser::exception_type &e) {
        return e.GetMsg().c_str();
    }

    return "";
}
