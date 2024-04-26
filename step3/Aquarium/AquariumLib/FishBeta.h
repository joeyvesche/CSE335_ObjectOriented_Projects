/**
 * @file FishBeta.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_FISHBETA_H
#define AQUARIUM_FISHBETA_H

#include "Item.h"

class FishBeta : public Item {
private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mFishImage;

    /// The bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    FishBeta() = delete;

    /// Copy constructor (disabled)
    FishBeta(const FishBeta &) = delete;

    /// Assignment operator
    void operator=(const FishBeta &) = delete;

    FishBeta(Aquarium* aquarium);

    void Draw(wxDC* dc) override;

    bool HitTest(int x, int y) override;

    void Fishy() override;

};

#endif //AQUARIUM_FISHBETA_H
