/**
 * @file BurningBuildingCounter.cpp
 * @author joeyv
 */
#include "pch.h"
#include "BurningBuildingCounter.h"
#include "TileBuilding.h"

/**
* Visit a TileBuilding object
* @param building Building we are visiting
*/
void BurningBuildingCounter::VisitBuilding(TileBuilding* building)
{
    if(building->OnFire())
    {
        mNumBurning++;
        mBurning = true;
    }
}