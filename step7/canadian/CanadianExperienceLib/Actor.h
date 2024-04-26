/**
 * @file Actor.h
 * @author joeyv
 *
 * Class for actors in our drawings.
 */

#ifndef CANADIANEXPERIENCE_ACTOR_H
#define CANADIANEXPERIENCE_ACTOR_H

#include "Picture.h"
#include "AnimChannelPoint.h"

class Drawable;
class Picture;
/**
* Class for actors in our drawings.
*
* An actor is some graphical object that consists of
* one or more parts. Actors can be animated.
*/
class Actor {
private:
    /// The actor name
    std::wstring mName;

    /// Is this actor enabled (drawable)?
    bool mEnabled = true;

    /// The actor position
    wxPoint mPosition;

    /// Is this actor mouse clickable?
    bool mClickable = true;

    /// The root drawable
    std::shared_ptr<Drawable> mRoot;

    /// The drawables in drawing order
    std::vector<std::shared_ptr<Drawable>> mDrawablesInOrder;

    /// The picture that represents the actor
    Picture *mPicture = nullptr;

    /// The animation channel for animating the angle of this drawable
    AnimChannelPoint mChannel;

public:
    /// Destructor
    virtual ~Actor() {}
    Actor(const std::wstring &name);
    /// Default constructor (disabled)
    Actor() = delete;
    /// Copy constructor (disabled)
    Actor(const Actor &) = delete;
    /// Assignment operator
    void operator=(const Actor &) = delete;

    void SetRoot(std::shared_ptr<Drawable> root);
    void Draw(std::shared_ptr<wxGraphicsContext> graphics);
    std::shared_ptr<Drawable> HitTest(wxPoint pos);
    void AddDrawable(std::shared_ptr<Drawable> drawable);
    void SetPicture(Picture* picture);
    void SetKeyframe();
    void GetKeyframe();
    void SetTimeline(Timeline* timeline);

    /**
     * Get the actor name
     * @return Actor name
     */
    std::wstring GetName() const { return mName; }

    /**
     * The actor position
     * @return The actor position as a point
     */
    wxPoint GetPosition() const { return mPosition; }

    /**
     * The actor position
     * @param pos The new actor position
     */
    void SetPosition(wxPoint pos) { mPosition = pos; }


    /**
     * Actor is enabled
     * @return enabled status
     */
    bool IsEnabled() const { return mEnabled; }

    /**
     * Set Actor Enabled
     * @param enabled New enabled status
     */
    void SetEnabled(bool enabled) { mEnabled = enabled; }

    /**
     * Actor is clickable
     * @return true if actor is clickable
     */
    bool IsClickable() const { return mClickable; }

    /**
     * Actor clickable
     * @param clickable New clickable status
     */
    void SetClickable(bool clickable) { mClickable = clickable; }

    /**
     * Get the actor picture
     * @return Picture associated with actor
     */
     Picture* GetPicture() const { return mPicture; }

     /**
      * The point animation channel
      * @return pointer to animation channel
      */
      AnimChannelPoint* GetPositionChannel() { return & mChannel;}
};

#endif //CANADIANEXPERIENCE_ACTOR_H
