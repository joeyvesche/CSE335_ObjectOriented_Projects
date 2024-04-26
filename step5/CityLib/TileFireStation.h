/**
 * @file TileFireStation.h
 * @author Charles Owen
 *
 * Class that implements a fire station tile
 */

#ifndef CITY_TILEFIRESTATION_H
#define CITY_TILEFIRESTATION_H

#include "Tile.h"


/**
 * Class that implements a fire station tile
 */
class TileFireStation : public Tile {
private:
    /// The fire station state possibilities
    enum class State {Ready, Opening, OneEngine, TwoEngines};

    /// The current fire station state
    State mState = State::Ready;
    int mFireStationImageDuration;


public:
    TileFireStation(City *city);

    /// Default constructor (disabled)
    TileFireStation() = delete;

    /// Copy constructor (disabled)
    TileFireStation(const TileFireStation &) = delete;

    /// Assignment operator
    void operator=(const TileFireStation &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Update(double elapsed) override;
    void ExtinguishBuilding();

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitFireStation(this); }
};

#endif //CITY_TILEFIRESTATION_H
