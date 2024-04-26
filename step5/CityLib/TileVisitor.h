/**
 * @file TileVisitor.h
 * @author joeyv
 *
 *
 */

#ifndef CITY_TILEVISITOR_H
#define CITY_TILEVISITOR_H

// Forward references to all tile types
class TileBuilding;
class TileLandscape;
class TileGarden;
class TileFireStation;
class TileWater;


/** Tile visitor base class */
class TileVisitor {
private:

public:
    virtual ~TileVisitor() {}

    /**
     * Visit a TileBuilding object
     * @param building Building we are visiting
     */
    virtual void VisitBuilding(TileBuilding* building) {}

    /**
     * Visit a TileLandscape object
     * @param landscape Landscape tile we are visiting
     */
    virtual void VisitLandscape(TileLandscape* landscape) {}

    /**
     * Visit a TileGarden object
     * @param garden Garden we are visiting
     */
    virtual void VisitGarden(TileGarden* garden) {}

    /**
     * Visit a water file
     * @param water Tile object we are visiting
     */
    virtual void VisitWater(TileWater* water) {}

    /**
     * Visit a FireStation object
     * @param firestation FireStation tile we are visiting
     */
     virtual void VisitFireStation(TileFireStation* firestation) {}
};

#endif //CITY_TILEVISITOR_H
