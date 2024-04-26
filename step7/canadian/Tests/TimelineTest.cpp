/**
 * @file TimelineTest.cpp
 * @author joeyv
 */

#include <pch.h>
#include <Timeline.h>
#include <gtest/gtest.h>
#include <AnimChannelAngle.h>

TEST(TestTimelineNumFrames, Frames)
{
    Timeline timeline;

    // numFrames getter and setter
    ASSERT_EQ(timeline.GetNumFrames(), 300);

    // setter
    timeline.SetNumFrames(44);
    ASSERT_EQ(timeline.GetNumFrames(), 44);

}

TEST(TestTimelineFrameRate, Frames)
{
    Timeline timeline;

    // numFrames getter and setter
    ASSERT_EQ(timeline.GetFrameRate(), 30);

    // setter
    timeline.SetFrameRate(60);
    ASSERT_EQ(timeline.GetFrameRate(), 60);

}

TEST(TestTimelineCurrentTime, Current)
{
    Timeline timeline;

    // numFrames getter and setter
    ASSERT_NEAR(timeline.GetCurrentTime(), 0, 0.00001);

    // setter
    timeline.SetCurrentTime(30.32444);
    ASSERT_NEAR(timeline.GetCurrentTime(), 30.32444, 0.000001);

}

TEST(TimelineTest, GetDuration)
{
    Timeline timeline;

    // Default value
    ASSERT_NEAR(10, timeline.GetDuration(), 0.0001);

    // Changed duration
    timeline.SetFrameRate(375);
    ASSERT_NEAR(300.0 / 375.0, timeline.GetDuration(), 0.0001);

    timeline.SetNumFrames(789);
    ASSERT_NEAR(789.0 / 375.0, timeline.GetDuration(), 0.0001);
}

TEST(TimelineTest, GetCurrentFrame)
{
    Timeline timeline;

    // Default value
    ASSERT_EQ(0, timeline.GetCurrentFrame());

    // Changed time
    timeline.SetCurrentTime(9.27);
    ASSERT_EQ(278, timeline.GetCurrentFrame());
}

TEST(TimelineTest, Add)
{
    Timeline timeline;
    AnimChannelAngle channel;

    timeline.AddChannel(&channel);
    ASSERT_EQ(&timeline, channel.GetTimeline());
}