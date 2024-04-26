/**
 * @file ViewTimeline.cpp
 * @author Charles B. Owen
 */

#include "pch.h"

#include <wx/dcbuffer.h>
#include <wx/xrc/xmlres.h>
#include <sstream>
#include <wx/stdpaths.h>

#include "ViewTimeline.h"
#include "TimelineDlg.h"
#include "Timeline.h"
#include "Picture.h"
#include "Actor.h"

using namespace std;

/// Y location for the top of a tick mark
const int TickTop = 15;

/// The spacing between ticks in the timeline
const int TickSpacing = 4;

/// The length of a short tick mark
const int TickShort = 10;

/// The length of a long tick mark
const int TickLong = 20;

/// Size of the tick mark labels
const int TickFontSize = 15;

/// Space to the left of the scale
const int BorderLeft = 10;

/// Space to the right of the scale
const int BorderRight = 10;

/// Space from the top of the scale
const int BorderTop = 20;

/// Filename for the pointer image
const std::wstring PointerImageFile = L"/pointer.png";

/**
 * Constructor
 * @param parent The main wxFrame object
 * @param imagesDir The directory the images are stored in
 */
ViewTimeline::ViewTimeline(wxFrame* parent, std::wstring imagesDir) :
    wxScrolledCanvas(parent,
            wxID_ANY,
            wxDefaultPosition,
            wxSize(100, Height),
            wxBORDER_SIMPLE)
{
    SetBackgroundStyle(wxBG_STYLE_PAINT);

    Bind(wxEVT_PAINT, &ViewTimeline::OnPaint, this);
    Bind(wxEVT_LEFT_DOWN, &ViewTimeline::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &ViewTimeline::OnLeftUp, this);
    Bind(wxEVT_MOTION, &ViewTimeline::OnMouseMove, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED,
            &ViewTimeline::OnEditTimelineProperties, this,
            XRCID("EditTimelineProperties"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &ViewTimeline::OnEditDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));
    parent->Bind(wxEVT_COMMAND_TOOL_CLICKED, &ViewTimeline::OnUpdateSetKeyframe, this, XRCID("EditSetKeyframe"));
    parent->Bind(wxEVT_COMMAND_TOOL_CLICKED, &ViewTimeline::OnUpdateDeleteKeyframe, this, XRCID("EditDeleteKeyframe"));

    mPointerImage = make_unique<wxImage>(imagesDir + PointerImageFile, wxBITMAP_TYPE_ANY);
}


/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void ViewTimeline::OnPaint(wxPaintEvent& event)
{
    auto size = GetPicture()->GetSize();
    SetVirtualSize(size.GetWidth(), size.GetHeight());
    SetScrollRate(1,0);

    wxAutoBufferedPaintDC dc(this);
    DoPrepareDC(dc);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    // Create a graphics context
    auto graphics = std::shared_ptr<wxGraphicsContext>(wxGraphicsContext::Create( dc ));

    wxPen pen(wxColour(0, 8, 0), 1);
    graphics->SetPen(pen);

    wxFont font(wxSize(0, 16),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    graphics->SetFont(font, *wxBLACK);

    Timeline *timeline = GetPicture()->GetTimeline();


    int currentTick = timeline->GetCurrentFrame() * TickSpacing + BorderLeft - 2;
    mPointerBitmap = graphics->CreateBitmapFromImage(*mPointerImage);

    graphics->DrawBitmap(mPointerBitmap,
            currentTick, BorderTop,
            mPointerImage->GetWidth(),
            mPointerImage->GetHeight());

    for(int tickNum = 0; tickNum <= timeline->GetNumFrames(); ++tickNum)
    {
        bool onSecond = (tickNum % timeline->GetFrameRate()) == 0;
        int drawAt = ((tickNum + 1) * TickSpacing) + BorderLeft;

        if (onSecond)
        {
            // Convert the tick number to seconds in a string
            std::wstringstream str;
            str << tickNum / timeline->GetFrameRate();
            std::wstring wstr = str.str();

            double w, h;
            graphics->GetTextExtent(wstr, &w, &h);

            graphics->StrokeLine(drawAt, BorderTop, drawAt, BorderTop + TickLong);
            graphics->DrawText(wstr.c_str(),drawAt - (float)(w)/2, float(BorderTop + TickLong));
        }
        else
        {
            graphics->StrokeLine(drawAt, BorderTop, drawAt, BorderTop + TickShort);
        }

    }

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void ViewTimeline::OnLeftDown(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    int x = click.x;

    // Get the timeline
    Timeline *timeline = GetPicture()->GetTimeline();
    int pointerX = (int)(timeline->GetCurrentTime() *
            timeline->GetFrameRate() * TickSpacing + BorderLeft);

    mMovingPointer = x >= pointerX - mPointerImage->GetWidth() / 2 &&
            x <= pointerX + mPointerImage->GetWidth() / 2;


}

/**
* Handle the left mouse button up event
* @param event
*/
void ViewTimeline::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);
}

/**
* Handle the mouse move event
* @param event
*/
void ViewTimeline::OnMouseMove(wxMouseEvent &event)
{
    auto click = CalcUnscrolledPosition(event.GetPosition());

    Timeline *timeline = GetPicture()->GetTimeline();
    int x = click.x;

    if(mMovingPointer && event.LeftIsDown())
    {
        if (x < BorderLeft)
        {
            GetPicture()->SetAnimationTime(0.0);
        }

        else if (x < BorderLeft + timeline->GetNumFrames() * TickSpacing)
        {
            double timer = double((x - BorderLeft)) / ((timeline->GetFrameRate()) * TickSpacing);

            GetPicture()->SetAnimationTime(timer);
        }

        else
        {
            GetPicture()->SetAnimationTime(timeline->GetDuration());
        }
    }
}

/**
 * Force an update of this window when the picture changes.
 */
void ViewTimeline::UpdateObserver()
{
    Refresh();
    Update();
}

/**
 * Handle an Edit>Timeline Properties... menu option
 * @param event The menu event
 */
void ViewTimeline::OnEditTimelineProperties(wxCommandEvent& event)
{

    std::shared_ptr<Picture> pic = GetPicture();
    TimelineDlg dlg(this->GetParent(), pic->GetTimeline());
    if (dlg.ShowModal() == wxID_OK)
    {
        pic->UpdateObservers();
    }

}

/**
 * Handle the Edit>Set Keyframe menu option
 * @param event Menu event
 */
void ViewTimeline::OnEditSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}


/**
 * Handle the Edit>Delete Keyframe menu option
 * @param event Menu event
 */
void ViewTimeline::OnEditDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    auto timeline = GetPicture()->GetTimeline();
    timeline->RemoveChannel();
    picture->SetAnimationTime(picture->GetAnimationTime());

}

/**
 * Update the menu for Edit>Set Keyframe
 * @param event Menu event
 */
void ViewTimeline::OnUpdateSetKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    for (auto actor : *picture)
    {
        actor->SetKeyframe();
    }
}

/**
* Update the menu for Edit>Delete Keyframe
 * @param event Menu event
*/
void ViewTimeline::OnUpdateDeleteKeyframe(wxCommandEvent& event)
{
    auto picture = GetPicture();
    auto timeline = GetPicture()->GetTimeline();
    timeline->RemoveChannel();
    picture->SetAnimationTime(picture->GetAnimationTime());
}