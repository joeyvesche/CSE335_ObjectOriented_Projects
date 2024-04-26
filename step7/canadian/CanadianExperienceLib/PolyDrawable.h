/**
 * @file PolyDrawable.h
 * @author joeyv
 *
 *
 */

#ifndef CANADIANEXPERIENCE_POLYDRAWABLE_H
#define CANADIANEXPERIENCE_POLYDRAWABLE_H

#include "Drawable.h"
#include <memory>

/**
 * A drawable based on polygon images.
 *
 * This class has a list of points and draws a polygon
 * drawable based on those points.
 */
class PolyDrawable : public Drawable{
private:
    /// The polygon color
    wxColour mColor = *wxBLACK;

    /// vector of point objects
    std::vector<wxPoint> mPoints;

    /// The transformed graphics path used
    /// to draw this polygon
    wxGraphicsPath mPath;


public:
    virtual ~PolyDrawable();

    PolyDrawable(const std::wstring &name);

    /// Default constructor disabled
    PolyDrawable() = delete;

    /// Copy constructor disabled
    PolyDrawable(const PolyDrawable&) = delete;

    /// Assignment operator disabled
    void operator=(const PolyDrawable&) = delete;

    void AddPoint(wxPoint point);
    virtual void Draw(std::shared_ptr<wxGraphicsContext> graphics) override;
    virtual bool HitTest(wxPoint pos) override;

    /** Set the color
     * @param color The new color*/
    void SetColor(wxColour color) { mColor = color; }

    /** Get the color
     * @returns The color*/
    wxColor GetColor() const { return mColor; }

};

#endif //CANADIANEXPERIENCE_POLYDRAWABLE_H
