//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_GAMESLOT_H
#define GFXFRAMEWORK_GAMESLOT_H

#include "PassiveGameObject.h"

class GameSlot : public PassiveGameObject {
public:
    explicit GameSlot(float side);

    float getSide() const;

    void setSide(float side);

protected:
    float side;
};


#endif //GFXFRAMEWORK_GAMESLOT_H
