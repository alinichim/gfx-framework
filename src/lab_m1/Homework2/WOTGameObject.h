//
// Created by alini on 12/14/2023.
//


#ifndef GFXFRAMEWORK_WOTGAMEOBJECT_H
#define GFXFRAMEWORK_WOTGAMEOBJECT_H

#include "utils/glm_utils.h"

class WOTGameObject {
public:
    WOTGameObject(const glm::vec3 &position, const glm::vec3 &forward);

    WOTGameObject();

    virtual bool collision(glm::vec3 point) = 0;

    glm::vec3 getPosition();

    void setPosition(glm::vec3 position);

    glm::vec3 getForward();

    void setForward(glm::vec3 forward);

protected:
    glm::vec3 position;
    glm::vec3 forward;
};


#endif //GFXFRAMEWORK_WOTGAMEOBJECT_H
