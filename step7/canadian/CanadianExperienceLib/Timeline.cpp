/**
 * @file Timeline.cpp
 * @author joeyv
 */

#include "pch.h"
#include "Timeline.h"
#include "AnimChannel.h"

/**
 * Constructor
 */
Timeline::Timeline()
{
}

/**
* Adding the channel to the timeline
 * @param channel The channel to be added
*/
void Timeline::AddChannel(AnimChannel* channel)
{
    mChannels.push_back(channel);
    channel->SetTimeline(this);
}

/**
* removing the channel from the timeline
*/
void Timeline::RemoveChannel()
{
    for (auto curChannel : mChannels)
    {
        curChannel->RemoveKeyFrame(GetCurrentFrame());
    }

}

/**
 * Sets the current time
 *
 * Ensures all of the channels are
 * valid for that point in time.
 * @param t The new time to set
 */
void Timeline::SetCurrentTime(double t)
{
    // Set the time
    mCurrentTime = t;

    for (auto channel : mChannels)
    {
        channel->SetFrame(GetCurrentFrame());
    }
}