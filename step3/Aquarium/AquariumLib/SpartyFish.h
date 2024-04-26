/**
 * @file SpartyFish.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_SPARTYFISH_H
#define AQUARIUM_SPARTYFISH_H

#include "Item.h"

class SpartyFish : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    SpartyFish() = delete;

    /// Copy constructor (disabled)
    SpartyFish(const SpartyFish &) = delete;

    /// Assignment operator
    void operator=(const SpartyFish &) = delete;

    SpartyFish(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

    void Fishy() override;

};

#endif //AQUARIUM_SPARTYFISH_H
