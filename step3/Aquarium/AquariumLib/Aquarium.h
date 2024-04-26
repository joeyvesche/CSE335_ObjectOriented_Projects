/**
 * @file Aquarium.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H

#include <memory>

#include "Item.h"

class Item;

class Aquarium  {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

    /// All of the items to populate our aquarium
    std::vector<std::shared_ptr<Item>> mItems;

public:
    Aquarium();

    void OnDraw(wxDC* dc);

    void Add(std::shared_ptr<Item> item);

    std::shared_ptr<Item> HitTest(int x, int y);

    void SendToFront(std::shared_ptr<Item> item);

    bool KillFish(double startX,double startY);
};

#endif //AQUARIUM_AQUARIUM_H
