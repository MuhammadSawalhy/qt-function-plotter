#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "plot_settings.hpp"

using namespace testing;

TEST(ValidateFuntion, ShouldNotAcceptEmptyExpressions)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = 2;
    newSettings.function = "";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(!errMsg.empty());
}

TEST(ValidateFuntion, ShouldNotAcceptInvalidExpressions)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = 2;
    newSettings.function = "1 -";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(!errMsg.empty());
}

TEST(ValidateFuntion, ShouldAcceptValidExpressions)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = 2;
    newSettings.function = "x + 1 / 3 ^ x - 12.5";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(errMsg.empty());
}

TEST(UpdatePlotSettings, ShouldUpdateWhenMaxIsGreaterThanMin)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = 1;
    newSettings.function = "x";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(errMsg.empty());
}

TEST(UpdatePlotSettings, ShouldNotUpdateWhenMaxEqualsMin)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = -1;
    newSettings.function = "x";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(!errMsg.empty());
}

TEST(UpdatePlotSettings, ShouldNotUpdateWhenMaxIsLessThanMin)
{
    PlotSettings newSettings;
    newSettings.minX = -1;
    newSettings.maxX = -2;
    newSettings.function = "x";
    std::string errMsg = updatePlotSettings(newSettings);
    ASSERT_TRUE(!errMsg.empty());
}
