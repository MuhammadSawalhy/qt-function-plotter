#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>
#include "plot_settings.hpp"

using namespace testing;

TEST(plot_settings_tests, validateFunctionTests)
{
    EXPECT_EQ(2, 2);
    ASSERT_THAT(0, Eq(0));
}

