/**
 * @file DoubleClickVisitor.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_DOUBLECLICKVISITOR_H
#define CITY_DOUBLECLICKVISITOR_H

#include "TileBuilding.h"

class DoubleClickVisitor : public TileVisitor {
private:

public:
    void VisitBuilding(TileBuilding* building);

};

#endif //CITY_DOUBLECLICKVISITOR_H
