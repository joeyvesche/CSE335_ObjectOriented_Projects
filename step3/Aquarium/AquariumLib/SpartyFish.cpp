/**
 * @file SpartyFish.cpp
 * @author joeyv
 */

#include "pch.h"
#include "SpartyFish.h"
#include "Aquarium.h"
#include <string>

using namespace std;

/// Fish filename
const wstring SpartyFishImageName = L"images/sparty-fish.png";

/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
SpartyFish::SpartyFish(Aquarium *aquarium) : Item(aquarium)
{
    mFishImage = make_unique<wxImage>(SpartyFishImageName, wxBITMAP_TYPE_ANY);
    mFishBitmap = make_unique<wxBitmap>(*mFishImage);
}

/**
 * Draw this fish
 * @param dc Device contect to draw on
 */
void SpartyFish::Draw(wxDC* dc)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();
    dc->DrawBitmap(*mFishBitmap,
            int(GetX() - wid / 2),
            int(GetY() - hit / 2));

}

/**
* Test to see if we hit this object with a mouse.
* @param x X position to test
* @param y Y position to test
* @return true if hit.
*/
bool SpartyFish::HitTest(int x, int y)
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
 * Virtual
 */
void SpartyFish::Fishy(){}
