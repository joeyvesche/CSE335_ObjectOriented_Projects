/**
 * @file TileBuilding.cpp
 * @author Charles B. Owen
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include "TileBuilding.h"
#include "City.h"
#include "MemberReport.h"


/// Number of fire images for a building
const int BuildingFireNumImages = 5;

/// The building fire images
const std::wstring BuildingFireImages[BuildingFireNumImages] = {L"fire1.png", L"fire2.png", L"fire3.png", L"fire4.png", L"fire5.png"};

/// Image for burnt out lot
const std::wstring BuildingFireImageBurnt = L"firedone.png";

/// How long each building fire image lasts
const double BuildingFireImageDuration = 0.3;



/**
 * Constructor
 * @param city The city this is a member of
*/
TileBuilding::TileBuilding(City *city) : Tile(city)
{
}

/**
 *  Set the image file to draw
 * @param file The base filename. Blank files are allowed
 */
void TileBuilding::SetImage(const std::wstring& file)
{
    // This save the first image supplied to SetImage to
    // a member variable so we can restore it later on
    if(!file.empty() && mBuildingImageFile.empty())
    {
        mBuildingImageFile = file;
    }

    Tile::SetImage(file);
}



/**
 * Update the building animation in time
 * @param elapsed Elapsed time in seconds
 */
void TileBuilding::Update(double elapsed)
{
    Tile::Update(elapsed);

    if(mState == State::Fire)
    {
        mFireImageDuration += elapsed;
        if(mFireImageDuration >= BuildingFireImageDuration)
        {
            mFireImageDuration -= BuildingFireImageDuration;

            mFireImageIndex = (mFireImageIndex + 1) % BuildingFireNumImages;
            SetImage(BuildingFireImages[mFireImageIndex]);
        }
    }
}


/**
 * Set the building on fire
 */
void TileBuilding::SetOnFire()
{
    // Set the fire state
    mState = State::Fire;
    mFireImageDuration = 0;
    mFireImageIndex = 0;

    // Set the first fire image
    SetImage(BuildingFireImages[mFireImageIndex]);
}

/**
 * Reset back to normal building state
 */
void TileBuilding::Reset()
{
        mState = State::Normal;
        SetImage(mBuildingImageFile);
}


/**
 * Extinguish any fire
 */
void TileBuilding::ExtinguishFire()
{
    if(mState == State::Fire)
    {
        mState = State::Burnt;
        SetImage(BuildingFireImageBurnt);
    }
}


/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileBuilding::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"building");
    itemNode->AddAttribute(L"file", mBuildingImageFile);

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileBuilding::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
    SetImage(node->GetAttribute(L"file").ToStdWstring());
}

/**
 * Generate a report for this  tile.
 * @param report
*/
void TileBuilding::Report(std::shared_ptr<MemberReport> report)
{
    std::wstringstream str;
    str << L"Building - " << GetFile();

    report->SetReport(str.str());
}

/**
 * Set the building on fire if double-clicked
 */
void TileBuilding::DoubleClick()
{
    if(!OnFire())
    {
        SetOnFire();
        mBurnt = true;
    }

}
