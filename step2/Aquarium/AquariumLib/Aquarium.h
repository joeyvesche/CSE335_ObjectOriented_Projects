/**
 * @file Aquarium.h
 * @author joeyv
 *
 *
 */

#ifndef AQUARIUM_AQUARIUM_H
#define AQUARIUM_AQUARIUM_H
#include <memory>

class Aquarium {
private:
    std::unique_ptr<wxBitmap> mBackground;  ///< Background image to use

public:
    void OnDraw(wxDC* dc);

    /**
 * Aquarium Constructor
 */
    Aquarium()
    {
        mBackground = std::make_unique<wxBitmap>(
                L"images/background1.png", wxBITMAP_TYPE_ANY);

    }

};

#endif //AQUARIUM_AQUARIUM_H