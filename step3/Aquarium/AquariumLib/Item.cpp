/**
 * @file Item.cpp
 * @author joeyv
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"

using namespace std;

/**
 * Constructor
 * @param aquarium The aquarium this item is a member of
 */
Item::Item(Aquarium *aquarium)
{
}

/**
 * Destructor
 */
Item::~Item()
{

}

/**
* Compute the distance from this item to another item
 * @param item Item we are computing the distance to
 * @return Distance in pixels
*/
double Item::DistanceTo(shared_ptr<Item> item)
{
    auto dx = item->GetX() - GetX();
    auto dy = item->GetY() - GetY();
    double d = sqrt(dx * dx + dy * dy);
    return sqrt(dx * dx + dy * dy);

}
