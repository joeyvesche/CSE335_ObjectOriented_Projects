/**
 * @file DoubleClickVisitor.cpp
 * @author joeyv
 */

#include "pch.h"
#include "DoubleClickVisitor.h"
#include "CityView.h"

/**
* Handle a double-click on a building
 * @param building Building to a double-click on
*/

void DoubleClickVisitor::VisitBuilding(TileBuilding* building)
{
    building->DoubleClick();
}