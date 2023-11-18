//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_BOARDSLOT_H
#define GFXFRAMEWORK_BOARDSLOT_H

#include "GameSlot.h"

class BoardSlot : public GameSlot {
public:

    Mesh *getMesh() override;
};


#endif //GFXFRAMEWORK_BOARDSLOT_H
