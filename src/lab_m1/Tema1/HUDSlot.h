//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_HUDSLOT_H
#define GFXFRAMEWORK_HUDSLOT_H

#include "GameSlot.h"

class HUDSlot : public GameSlot {

public:
    HUDSlot(float side, int price);

    Mesh *getMesh() override;

    int getPrice() const;

    void setPrice(int price);

private:
    int price;
};


#endif //GFXFRAMEWORK_HUDSLOT_H
