/**
 * @file LimpetFish.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_LIMPETFISH_H
#define AQUARIUM_LIMPETFISH_H

#include "Item.h"
#include "AquariumView.h"

class LimpetFish : public Item, Aquarium{
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    LimpetFish() = delete;

    /// Copy constructor (disabled)
    LimpetFish(const LimpetFish &) = delete;

    /// Assignment operator
    void operator=(const LimpetFish &) = delete;

    LimpetFish(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

    void Fishy() override;



};

#endif //AQUARIUM_LIMPETFISH_H
