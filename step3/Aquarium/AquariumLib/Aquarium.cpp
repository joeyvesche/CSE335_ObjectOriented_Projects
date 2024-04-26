/**
 * @file Aquarium.cpp
 * @author joeyv
 */
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "Item.h"

using namespace std;

/**
 * Aquarium Constructor
 */
Aquarium::Aquarium()
{
    mBackground = std::make_unique<wxBitmap>(
            L"images/background1.png", wxBITMAP_TYPE_ANY);

}

/**
 * Draw the aquarium
 * @param dc The device context to draw on
 */
void Aquarium::OnDraw(wxDC *dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);

    wxFont font(wxSize(0, 20),
            wxFONTFAMILY_SWISS,
            wxFONTSTYLE_NORMAL,
            wxFONTWEIGHT_NORMAL);
    dc->SetFont(font);
    dc->SetTextForeground(wxColour(0, 64, 0));
    dc->DrawText(L"Under the Sea!", 10, 10);

    for(auto item : mItems)
    {
        item->Draw(dc);
    }
}

/// Initial fish X location
const int InitialX = 200;

/// Initial fish Y location
const int InitialY = 200;

/** Add an item to the aquarium
 * @param item New item to add
 */
void Aquarium::Add(std::shared_ptr<Item> item)
{
    int x = 10;
    int y = 10;

    if (mItems.empty())
    {
        item->SetLocation(InitialX, InitialY);
        mItems.push_back(item);
    }

    else {
        item->SetLocation(InitialX, InitialY);
        for (auto k : mItems) {

            if(item->DistanceTo(k) < 1)
            {
                item->SetLocation(InitialX + x, InitialY + y);
                x += 10;
                y += 10;

                for(auto j:mItems)
                {
                    if(item->DistanceTo(j) < 1)
                    {
                        item->SetLocation(InitialX + x, InitialY + y);
                        x += 10;
                        y += 10;
                    }
                }
            }
        }
        mItems.push_back(item);
    }
}

/**
 * Test an x,y click location to see if it clicked
 * on some item in the aquarium.
 * @param x X location in pixels
 * @param y Y location in pixels
 * @returns Pointer to item we clicked on or nullptr if none.
*/
std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend();  i++)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }

    return  nullptr;
}

/**
 * Sends an item to the front of a vector
 * @param item
 */
void Aquarium::SendToFront(shared_ptr<Item> item)
{
    auto loc = find(begin(mItems), end(mItems), item);
    if(loc != end(mItems))
    {
        mItems.erase(loc);
    }
    mItems.push_back(item);
}

/**
 * Deletes fish in the triangle
 * @param startX,startY
 */
bool Aquarium::KillFish(double startX, double startY)
{
    for(auto item: mItems) {

        double itemX = item->GetX();
        double itemY = item->GetY(); // The x,y center of the item we are testing
      //  double startX = GetX();
       // double startY = GetY(); // The point of the kill triangle
        double range = 160; // The kill triangle range
        double spread = 400; // The kill triangle spread

        // How far the item is from the start in the x dimension
        double dx = itemX-startX;
        if (dx>=0 && dx<=range) {
            // We are in the correct range in the X dimension
            double dy = itemY-startY;

            // What is the range in the Y dimension at this point?
            double maxY = (spread/2)*dx/range;
            if (dy>=-maxY && dy<=maxY) {
                // The kill value is within that Y range
                // KILL

                for (int i = 0; i<mItems.size(); i++) {
                    if (mItems[i]==item) {
                        mItems.erase(mItems.begin()+i);
                        break;
                    }
                }
                return true;
            }
        }
    }
}