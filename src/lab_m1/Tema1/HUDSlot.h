//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_HUDSLOT_H
#define GFXFRAMEWORK_HUDSLOT_H

#include "GameSlot.h"

class HUDSlot : public GameSlot {

public:
    Mesh *getMesh() override;
};


#endif //GFXFRAMEWORK_HUDSLOT_H
