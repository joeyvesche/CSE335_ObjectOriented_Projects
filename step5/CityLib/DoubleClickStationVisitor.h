/**
 * @file DoubleClickStationVisitor.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_DOUBLECLICKSTATIONVISITOR_H
#define CITY_DOUBLECLICKSTATIONVISITOR_H

#include "TileFireStation.h"
#include "TileBuilding.h"

class DoubleClickStationVisitor : public TileVisitor {
private:

public:
    void VisitFireStation(TileFireStation* firestation);

};

#endif //CITY_DOUBLECLICKSTATIONVISITOR_H
