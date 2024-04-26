/**
 * @file AquariumView.cpp
 * @author joeyv
 */
#include "pch.h"
#include "AquariumView.h"
#include "ids.h"
#include "FishBeta.h"
#include "Aquarium.h"
#include "SpartyFish.h"
#include "StinkyFish.h"
#include "LimpetFish.h"
#include "Item.h"
#include <wx/dcbuffer.h>

using namespace std;

/**
 * Paint event, draws the window.
 * @param event Paint event object
 */
void AquariumView::OnPaint(wxPaintEvent& event)
{
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mAquarium.OnDraw(&dc);
}
/**
 * Initialize the aquarium view class.
 * @param parent The parent window for this class
 */
void AquariumView::Initialize(wxFrame* parent)
{
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);

    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddSpartyFish, this, IDM_ADDFISHNEMO);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddStinkyFish, this, IDM_ADDFISHANGEL);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddLimpetFish, this, IDM_ADDFISHCARP);



    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_LEFT_DCLICK, &AquariumView::OnDoubleClick, this);
}


/**
 * Menu handler for Add Fish>Beta Fish
 * @param event Mouse event
 */
void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();

}

/**
 * Menu handler for add Fish>Sparty Fish
 * @param event Mouse event
 */
void AquariumView::OnAddSpartyFish(wxCommandEvent& event)
{
    auto fish = make_shared<SpartyFish>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}
/**
 * Menu handler for add Fish>Stinky Fish
 * @param event Mouse event
 */
void AquariumView::OnAddStinkyFish(wxCommandEvent& event)
{
    auto fish = make_shared<StinkyFish>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

/**
 * Menu handler for add Fish>Limpet Fish
 * @param event Mouse event
 */
void AquariumView::OnAddLimpetFish(wxCommandEvent& event)
{
    auto fish = make_shared<LimpetFish>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();

}

/**
 * Handle the left mouse button down event
 * @param event
 */
void AquariumView::OnLeftDown(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        mAquarium.SendToFront(mGrabbedItem);
    }

}

/**,
* Handle the left mouse button down event
* @param event
*/
void AquariumView::OnLeftUp(wxMouseEvent &event)
{
    OnMouseMove(event);

}

/**
* Handle the left mouse button down event
* @param event
*/
void AquariumView::OnMouseMove(wxMouseEvent &event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to
        //move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the
            // item
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }

}

/**
* Handle the double click event
 * @param event
*/
void AquariumView::OnDoubleClick(wxMouseEvent &event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());
    if (mGrabbedItem != nullptr)
    {
        mAquarium.SendToFront(mGrabbedItem);
        mGrabbedItem->Fishy();
    }



}