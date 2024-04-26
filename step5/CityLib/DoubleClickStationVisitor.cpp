/**
 * @file DoubleClickStationVisitor.cpp
 * @author joeyv
 */

#include "pch.h"
#include "DoubleClickStationVisitor.h"
#include "CityView.h"

/**
* Handle a double-click on the FireStation
 * @param building Building to a double-click on
*/
void DoubleClickStationVisitor::VisitFireStation(TileFireStation* firestation)
{
    firestation->ExtinguishBuilding();
}

