/**
 * @file FireToBuilding.cpp
 * @author joeyv
 */
#include "pch.h"
#include "FireToBuilding.h"

/**
 * Handle Extinguishing the fire on a building
 * @param building Building to Extinguish
 */
void FireToBuilding::VisitBuilding(TileBuilding* building)
{
    if (building->OnFire()) {
        building->ExtinguishFire();
    }

}