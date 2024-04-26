/**
 * @file FireToBuilding.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_FIRETOBUILDING_H
#define CITY_FIRETOBUILDING_H

#include "TileVisitor.h"
#include "TileFireStation.h"
#include "TileBuilding.h"

class FireToBuilding : public TileVisitor {

private:

public:
    void VisitBuilding(TileBuilding* building);

};

#endif //CITY_FIRETOBUILDING_H
