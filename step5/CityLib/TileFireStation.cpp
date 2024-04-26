/**
 * @file TileFireStation.cpp
 * @author Charles Owen
 */

#include "pch.h"
#include <sstream>
#include <iostream>
#include <chrono>
#include <thread>
#include "TileFireStation.h"
#include "City.h"
#include "MemberReport.h"
#include "FireToBuilding.h"
#include "BurningBuildingCounter.h"

/// Image for the fire station with the doors closed
const std::wstring FireStationReadyImage = L"firestation1.png";

/// Image of the fire station with the doors opening
const std::wstring FireStationOpeningImage = L"firestation2.png";

/// Image of the fire station with one engine out
const std::wstring FireStationOneEngineImage = L"firestation3.png";

/// Image of the fire station with two engines out
const std::wstring FireStationTwoEnginesImage = L"firestation4.png";

/// Time the door opening image is displayed
const double FireStationDoorOpeningTime = 1.0;

/// Time one or two engines are displayed
const double FireStationEngineDisplayTime = 1.0;

/**
 * Constructor
 * @param city The city this is a member of
*/
TileFireStation::TileFireStation(City *city) : Tile(city)
{
    SetImage(FireStationReadyImage);
}

/**
 * Update the building animation in time
 * @param elapsed Elapsed time in seconds
 */
void TileFireStation::Update(double elapsed)
{
    Tile::Update(elapsed);

    switch(mState)
    {
        case State::Ready:
            mFireStationImageDuration += elapsed;
            if(mFireStationImageDuration >= FireStationDoorOpeningTime)
            {
                mState = State::Ready;
                mFireStationImageDuration = 0;
                SetImage(FireStationOpeningImage);
            }
            break;

            // One state presented as an example, the rest are up to you
        case State::Opening:
            mFireStationImageDuration += elapsed;
            if(mFireStationImageDuration >= FireStationDoorOpeningTime)
            {
                BurningBuildingCounter bvisitor; // number of burning buildings
                GetCity()->Accept(&bvisitor);
                int cnt = bvisitor.GetBurning();

                if(cnt == 1){
                    mState= State::OneEngine;
                    mFireStationImageDuration = 0;
                    SetImage(FireStationOneEngineImage);
                    break;

                }


                else if(cnt >= 2){
                    mState=State::TwoEngines;
                    mFireStationImageDuration = 0;
                    SetImage(FireStationTwoEnginesImage);
                    break;
                }

            }


        case State::OneEngine:
            mFireStationImageDuration += elapsed;
            if(mFireStationImageDuration >= FireStationEngineDisplayTime)
            {
                mState = State::Ready;
                mFireStationImageDuration = 0;
                SetImage(FireStationReadyImage);
            }
            break;


        case State::TwoEngines:
            mFireStationImageDuration += elapsed;
            if(mFireStationImageDuration >= FireStationEngineDisplayTime)
            {
                mState = State::Ready;
                mFireStationImageDuration = 0;
                SetImage(FireStationReadyImage);
            }
            break;


        default:
            break;
    }

}

/**  Save this item to an XML node
* @param node The node we are going to be a child of
* @return Allocated node
*/
wxXmlNode* TileFireStation::XmlSave(wxXmlNode* node)
{
    auto itemNode = Tile::XmlSave(node);

    itemNode->AddAttribute(L"type", L"fire-station");

    return itemNode;
}


/**
* brief Load the attributes for an item node.
* @param node The Xml node we are loading the item from
*/
void TileFireStation::XmlLoad(wxXmlNode* node)
{
    Tile::XmlLoad(node);
}



/**
 * Generate a report for this  tile.
 * @param report
*/
void TileFireStation::Report(std::shared_ptr<MemberReport> report)
{

    std::wstringstream str;
    str << L"Building - Fire Station";

    report->SetReport(str.str());
}

/**
 * Extinguish the buildings
 */
void TileFireStation::ExtinguishBuilding()
{
    FireToBuilding visitor; // Extinguishes the fire(s)

    BurningBuildingCounter bvisitor; // number of burning buildings
    GetCity()->Accept(&bvisitor);
    int cnt = bvisitor.GetBurning();


    if(cnt == 1)
    {
        SetImage(FireStationOpeningImage);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        SetImage(FireStationOneEngineImage);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        GetCity()->Accept(&visitor);

    }

    else if(cnt >= 2)
    {

        SetImage(FireStationOpeningImage);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        SetImage(FireStationTwoEnginesImage);
        std::this_thread::sleep_until(std::chrono::system_clock::now() + std::chrono::seconds(1));
        GetCity()->Accept(&visitor);

    }
}
