/**
 * @file AnimChannelPoint.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
#define CANADIANEXPERIENCE_ANIMCHANNELPOINT_H

#include "AnimChannel.h"

/**
 * Animation channel for points
 */
class AnimChannelPoint : public AnimChannel{
public:
    virtual ~AnimChannelPoint();

    /** Copy constructor disabled */
    AnimChannelPoint(const AnimChannelPoint&) = delete;

    /** Assignment operator disabled */
    void operator=(const AnimChannelPoint&) = delete;

    AnimChannelPoint();

    /** Get the point
    * @returns the point */
    wxPoint GetPoint() const { return mPoint; }

    void SetKeyframe(wxPoint point);

protected:
    /** Class that represents a keyframe */
    class KeyframePoint : public Keyframe
    {
    public:
        /** Get the point
        * @return the point */
        wxPoint GetPoint() const { return mPoint; }

        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        /** Use this keyframe as keyfraem 2 */
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

        /** Use this keyframe as the point */
        virtual void UseOnly() override { mChannel->mPoint = mPoint; }

        /** Constructor
        * @param channel The channel we are for
        * @param point The point for the keyframe */
        KeyframePoint(AnimChannelPoint* channel, wxPoint point) :
                Keyframe(channel), mChannel(channel), mPoint(point) {}

        /** Default constructor disabled */
        KeyframePoint() = delete;
        /** Copy constructor disabled */
        KeyframePoint(const KeyframePoint&) = delete;
        /** Assignment operator disabled */
        void operator=(const KeyframePoint&) = delete;

    private:
        /// The point
        wxPoint mPoint;
        /// The channel this keyframe is associated with
        AnimChannelPoint* mChannel;
    };

    virtual void Tween(double t) override;
private:
    /// the point
    wxPoint mPoint;

    /// The first angle keyframe
    KeyframePoint* mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframePoint* mKeyframe2 = nullptr;

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELPOINT_H
