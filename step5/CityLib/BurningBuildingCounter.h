/**
 * @file BurningBuildingCounter.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_BURNINGBUILDINGCOUNTER_H
#define CITY_BURNINGBUILDINGCOUNTER_H

#include "TileVisitor.h"

class BurningBuildingCounter : public TileVisitor {
private:
    int mNumBurning = 0;
    bool mBurning = false;

public:
    /**
     * Get the number of burning buildings
     * @return Number of buildings
     */
    int GetBurning() const { return mNumBurning; }
    bool IfBurning() const{return mBurning; }


    void VisitBuilding(TileBuilding* building);

};

#endif //CITY_BURNINGBUILDINGCOUNTER_H
