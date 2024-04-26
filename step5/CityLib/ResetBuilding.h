/**
 * @file ResetBuilding.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_RESETBUILDING_H
#define CITY_RESETBUILDING_H

#include "TileBuilding.h"


class ResetBuilding : public TileVisitor{
private:

public:
    void VisitBuilding(TileBuilding* building);

};

#endif //CITY_RESETBUILDING_H
