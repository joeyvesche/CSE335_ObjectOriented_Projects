/**
* @file TileBuilding.h
*
* @author Charles B. Owen
*
*  Class that implements a Building tile
*/

#pragma once

#include "Tile.h"


/**
*  A Building tile
*/
class TileBuilding : public Tile
{
private:
    /// The building image file
    std::wstring mBuildingImageFile;

    /// Possible building states
    enum class State {Normal, Fire, Burnt};

    /// The current building state
    State mState = State::Normal;

    /// Current fire image index
    int mFireImageIndex = 0;

    /// The duration for the current file image
    double mFireImageDuration = 0;

    /// If the building was already on fire
    bool mBurnt = false;

public:
    TileBuilding(City *city);

    ///  Default constructor (disabled)
    TileBuilding() = delete;

    ///  Copy constructor (disabled)
    TileBuilding(const TileBuilding &) = delete;

    wxXmlNode* XmlSave(wxXmlNode* node) override;
    void XmlLoad(wxXmlNode* node) override;

    virtual void Report(std::shared_ptr<MemberReport> report) override;

    void Update(double elapsed) override;

    /**
     * Is this building on fire?
     * @return True if on file
     */
    bool OnFire() {return mState == State::Fire;}

    void ExtinguishFire();

    void SetImage(const std::wstring& file) override;

    void SetOnFire();

    void Reset();

    void DoubleClick();
    bool CheckBurnt() const{return mBurnt;}

    /**
     * Accept a visitor
     * @param visitor The visitor we accept
     */
    void Accept(TileVisitor* visitor) override { visitor->VisitBuilding(this); }
};

