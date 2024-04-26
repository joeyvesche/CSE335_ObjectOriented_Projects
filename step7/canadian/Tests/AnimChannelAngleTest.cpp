/**
 * @file AnimChannelAngleTest.cpp
 * @author joeyv
 */

#include <pch.h>
#include <AnimChannelAngle.h>
#include "gtest/gtest.h"

TEST(TestAnimChannelAngleGettersAndSetters, Anim)
{
    AnimChannelAngle chan;
    chan.SetName(L"Channel1");

    ASSERT_EQ(chan.GetName(), std::wstring(L"Channel1"));
}
