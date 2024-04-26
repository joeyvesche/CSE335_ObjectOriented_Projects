/**
 * @file AnimChannelAngle.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
#define CANADIANEXPERIENCE_ANIMCHANNELANGLE_H

#include "AnimChannel.h"

/**
 * Animation channel for angles.
 */
class AnimChannelAngle : public AnimChannel{
public:
    virtual ~AnimChannelAngle();

    /** Copy constructor disabled */
    AnimChannelAngle(const AnimChannelAngle&) = delete;

    /** Assignment operator disabled */
    void operator=(const AnimChannelAngle&) = delete;

    AnimChannelAngle();

    /** Get the angle
    * @returns the angle */
    double GetAngle() const { return mAngle; }

    void SetKeyframe(double angle);

protected:
    /** Class that represents a keyframe */
    class KeyframeAngle : public Keyframe
    {
    public:
        /** Get the angle
        * @returns the angle */
        double GetAngle() const { return mAngle; }

        /// Use this keyframe as keyframe 1
        virtual void UseAs1() override { mChannel->mKeyframe1 = this; }

        /// Use this keyframe as keyfraem 2
        virtual void UseAs2() override { mChannel->mKeyframe2 = this; }

        /// Use this keyframe as the angle
        virtual void UseOnly() override { mChannel->mAngle = mAngle; }

        /** Constructor
        * @param channel The channel we are for
        * @param angle The angle for the keyframe */
        KeyframeAngle(AnimChannelAngle* channel, double angle) :
                Keyframe(channel), mChannel(channel), mAngle(angle) {}

        /** @brief Default constructor disabled */
        KeyframeAngle() = delete;
        /** @brief Copy constructor disabled */
        KeyframeAngle(const KeyframeAngle&) = delete;
        /** @brief Assignment operator disabled */
        void operator=(const KeyframeAngle&) = delete;

    private:
        /// the angle of the keyframe
        double mAngle;
        /// The channel this keyframe is associated with
        AnimChannelAngle* mChannel;
    };

    virtual void Tween(double t) override;

private:
    /// the angle
    double mAngle = 0;

    /// The first angle keyframe
    KeyframeAngle* mKeyframe1 = nullptr;

    /// The second angle keyframe
    KeyframeAngle* mKeyframe2 = nullptr;

};

#endif //CANADIANEXPERIENCE_ANIMCHANNELANGLE_H
