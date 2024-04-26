/**
 * @file AquariumView.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_AQUARIUMVIEW_H
#define AQUARIUM_AQUARIUMVIEW_H
#include "Aquarium.h"


/**
 * View class for our aquarium
 */
class AquariumView : public wxWindow {
private:
    void OnPaint(wxPaintEvent& event);
    /// An object that describes our aquarium
    Aquarium  mAquarium;

public:
    void Initialize(wxFrame* parent);
    void OnAddFishBetaFish(wxCommandEvent& event);
    void OnLeftDown(wxMouseEvent &event);
    void OnLeftUp(wxMouseEvent &event);
    void OnMouseMove(wxMouseEvent &event);
    void OnAddSpartyFish(wxCommandEvent& event);
    void OnAddStinkyFish(wxCommandEvent& event);
    void OnAddLimpetFish(wxCommandEvent& event);
    void OnDoubleClick(wxMouseEvent &event);

    /// Any item we are currently dragging
    std::shared_ptr<Item> mGrabbedItem;

};

#endif //AQUARIUM_AQUARIUMVIEW_H
