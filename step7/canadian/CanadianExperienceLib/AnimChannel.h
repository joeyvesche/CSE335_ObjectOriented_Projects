/**
 * @file AnimChannel.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_ANIMCHANNEL_H
#define CANADIANEXPERIENCE_ANIMCHANNEL_H

class Timeline;
/**
 * Base class for animation channels
 *
 * This class provides basic functionality and a polymorphic
 * representation for animation channels.
 */
class AnimChannel {
public:
    virtual ~AnimChannel();
    AnimChannel();

    /** Copy constructor disabled */
    AnimChannel(const AnimChannel&) = delete;

    /** Assignment operator disabled */
    void operator=(const AnimChannel&) = delete;

    /** Get the name
    * @returns the name */
    std::wstring GetName() const { return mName; }

    /** Set the name
    * @param name The name to set */
    void SetName(std::wstring name) { mName = name; }

    /** Get the timeline
    * @returns the timeline */
    Timeline* GetTimeline() const { return mTimeline; }

    /** Set the timeline
    * @param timeline The timeline to set */
    void SetTimeline(Timeline* timeline) { mTimeline = timeline; }

    void RemoveKeyFrame(int frame);
    bool IsValid();
    void SetFrame(int currFrame);

protected:

    /** Class that represents a keyframe */
    class Keyframe {
    public:
        /** Get the frame
        * @returns the frame */
        int GetFrame() const { return mFrame; }

        /** Set the frame
        * @param frame The name to set */
        void SetFrame(int frame) { mFrame = frame; }

        /** Use this keyframe as keyframe 1 */
        virtual void UseAs1() = 0;

        /** Use this keyframe as keyfraem 2 */
        virtual void UseAs2() = 0;

        /** Use this keyframe as the angle */
        virtual void UseOnly() = 0;

        /** @brief Default constructor disabled */
        Keyframe() = delete;

        /** @brief Copy constructor disabled */
        Keyframe(const Keyframe&) = delete;

        /** @brief Assignment operator disabled */
        void operator=(const Keyframe&) = delete;

    protected:
        /// the frame the key frame is at
        int mFrame;

        /** Constructor
        * @param channel Channel we are associated with */
        Keyframe(AnimChannel* channel) : mChannel(channel) { }

    private:
        /// The channel this keyframe is associated with
        AnimChannel* mChannel;

    };

        void InsertKeyframe(std::shared_ptr<Keyframe> keyframe);

        /**
         * Compute an angle that is an interpolation between two keyframes
         *
         * This function is called after Use1 and Use2, so we have pointers to
         * to valid keyframes of the type KeyframeAngle. This function does the
         * tweening.
         * @param t A t value. t=0 means keyframe1, t=1 means keyframe2. Other values
         * interpolate between.
         */
        virtual void Tween(double t) = 0;

    private:
        /// the name
        std::wstring mName;

        /// first keyframe
        int mKeyframe1 = -1;

        /// second keyframe
        int mKeyframe2 = -1;

        /// The timeline object
        Timeline *mTimeline = nullptr;

        /// The collection of keyframes for this channel
        std::vector<std::shared_ptr<Keyframe>> mKeyframes;

};

#endif //CANADIANEXPERIENCE_ANIMCHANNEL_H
