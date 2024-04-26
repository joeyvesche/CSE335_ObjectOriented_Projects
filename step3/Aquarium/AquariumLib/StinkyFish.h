/**
 * @file StinkyFish.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_STINKYFISH_H
#define AQUARIUM_STINKYFISH_H

#include "Item.h"

class StinkyFish : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    StinkyFish() = delete;

    /// Copy constructor (disabled)
    StinkyFish(const StinkyFish &) = delete;

    /// Assignment operator
    void operator=(const StinkyFish &) = delete;

    StinkyFish(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

    void Fishy() override;

};

#endif //AQUARIUM_STINKYFISH_H
