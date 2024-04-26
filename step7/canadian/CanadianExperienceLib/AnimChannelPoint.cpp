/**
 * @file AnimChannelPoint.cpp
 * @author joeyv
 */

#include "pch.h"
#include "AnimChannelPoint.h"

using namespace std;

/** Deconstructor */
AnimChannelPoint::~AnimChannelPoint()
{
}

/** Constructor */
AnimChannelPoint::AnimChannelPoint() : AnimChannel()
{
}

/**
 * Set the keyframe at the current frame
 *
 * @param point The point that the current keyframe will hold.
 */
void AnimChannelPoint::SetKeyframe(wxPoint point)
{
    // Create a keyframe of the appropriate type
    // Telling it this channel and the point
    shared_ptr<KeyframePoint> keyframe = make_shared<KeyframePoint>(this, point);

    // Insert it into the collection
    InsertKeyframe(keyframe);
}

/**
 * Compute an angle that is an interpolation between two keyframes
 *
 * This function is called after Use1 and Use2, so we have pointers to
 * to valid keyframes of the type KeyframeAngle. This function does the
 * tweening.
 * @param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
 * interpolate between.
 */
void AnimChannelPoint::Tween(double t)
{
    wxPoint a = mKeyframe1->GetPoint();
    wxPoint b = mKeyframe2->GetPoint();

    wxPoint c(int(a.x + t * (b.x - a.x)), int(a.y + t * (b.y - a.y)));

    mPoint = c;
}