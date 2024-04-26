/**
 * @file Timeline.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_TIMELINE_H
#define CANADIANEXPERIENCE_TIMELINE_H

class AnimChannel;
/**
 * This class implements a timeline that manages the animation
 *
 * A timeline consists of animation channels for different parts of our
 * actors, each with keyframes that set the position, orientation, etc
 * at that point in time.
 */
class Timeline {
private:
    /// number of frames
    int mNumFrames = 300;
    /// frames per second
    int mFrameRate = 30;
    /// current time for the animation
    double mCurrentTime = 0;

    /// List of all animation channels
    std::vector<AnimChannel *> mChannels;


public:
    /** Copy constructor disabled */
    Timeline(const Timeline&) = delete;

    /** Assignment operator disabled */
    void operator=(const Timeline&) = delete;

    Timeline();

    /**
     * Get the number of frames in the animation
     * @return Number of frames in the animation
     */
    int GetNumFrames() const {return mNumFrames;}

    /**
     * Set the number of frames in the animation
     * @param numFrames Number of frames in the animation
     */
    void SetNumFrames(int numFrames) {mNumFrames = numFrames;}

    /**
     * Get the frame rate
     * @return Animation frame rate in frames per second
     */
    int GetFrameRate() const {return mFrameRate;}

    /**
     * Set the frame rate
     * @param frameRate Animation frame rate in frames per second
     */
    void SetFrameRate(int frameRate) {mFrameRate = frameRate;}

    /**
     * Get the current time
     * @return Current animation time in seconds
     */
    double GetCurrentTime() const {return mCurrentTime;}

    /**
     * Get the animation duration
     * @return Animation duration in seconds
     */
    double GetDuration() const { return double(mNumFrames)/mFrameRate; }

    /** Get the current frame.
     *
     * This is the frame associated with the current time
     * @return Current frame
     */
    int GetCurrentFrame() const { return int(mFrameRate * mCurrentTime); }

    /**
     * Gets the list of animation channels
     * @return list of channels
     */
    std::vector<AnimChannel*> GetChannels() { return mChannels; }

    void AddChannel(AnimChannel* channel);
    void RemoveChannel();
    void SetCurrentTime(double t);

};

#endif //CANADIANEXPERIENCE_TIMELINE_H
