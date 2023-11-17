//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_BOARDSLOT_H
#define GFXFRAMEWORK_BOARDSLOT_H

#include "PassiveGameObject.h"

class BoardSlot : public PassiveGameObject {
public:
    BoardSlot();

    Mesh *getMesh() override;
};


#endif //GFXFRAMEWORK_BOARDSLOT_H
