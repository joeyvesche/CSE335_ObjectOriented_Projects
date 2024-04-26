/**
 * @file LimpetFish.cpp
 * @author joeyv
 */

#include "pch.h"
#include "LimpetFish.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring LimpetFishImageName = L"images/limpet.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
LimpetFish::LimpetFish(Aquarium *aquarium) : Item(aquarium)
{
    mFishImage = make_unique<wxImage>(LimpetFishImageName, wxBITMAP_TYPE_ANY);
    mFishBitmap = make_unique<wxBitmap>(*mFishImage);
}

/// X location of the mouth relative to the center of the fish in pixels
const int LimpetMouthX = 94;

/// Y location of the mouth relative to the center of the fish in pixels
const int LimpetMouthY = 13;

/// Range of a thrum in pixels in the X direction
const int LimpetThrumRange = 400;

/// Spread of the thrum in pixels in the Y direction up and down
/// at the farthest range.
const int LimpetThrumSpread = 160;

/**
 * Draw this fish
 * @param dc Device contect to draw on
 */
void LimpetFish::Draw(wxDC* dc)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();
    dc->DrawBitmap(*mFishBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));

    int mouthX = int(GetX() + LimpetMouthX);
    int mouthY = int(GetY() + LimpetMouthY);

    wxPen thrumPen(*wxRED, 2);
    dc->SetPen(thrumPen);
    dc->DrawLine(mouthX, mouthY, mouthX + LimpetThrumRange, mouthY - LimpetThrumSpread/2);
    dc->DrawLine(mouthX, mouthY, mouthX + LimpetThrumRange, mouthY + LimpetThrumSpread/2);

}

/**
* Test to see if we hit this object with a mouse.
* @param x X position to test
* @param y Y position to test
* @return true if hit.
*/
bool LimpetFish::HitTest(int x, int y)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();

    // Make x and y relative to the top-left corner of the bitmap image
    // Subtracting the center makes x, y relative to the image center
    // Adding half the size makes x, y relative to the image top corner
    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    // Test to see if x, y are in the image
    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        // We are outside the image
        return false;
    }

    // Test to see if x, y are in the drawn part of the image
    // If the location is transparent, we are not in the drawn
    // part of the image
    return !mFishImage->IsTransparent((int)testX, (int)testY);

}

/**
 * Virtual that calls the KillFish
 */
void LimpetFish::Fishy()
{
    Aquarium::KillFish(GetX(), GetY());
}

