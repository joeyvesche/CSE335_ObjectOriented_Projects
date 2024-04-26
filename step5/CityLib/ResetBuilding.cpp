/**
 * @file ResetBuilding.cpp
 * @author joeyv
 */
#include "pch.h"
#include "ResetBuilding.h"

void ResetBuilding::VisitBuilding(TileBuilding* building)
{
    building->Reset();

};