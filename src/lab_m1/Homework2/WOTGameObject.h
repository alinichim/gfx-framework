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

    const glm::vec3 &getPosition() const;

    void setPosition(const glm::vec3 &position);

    const glm::vec3 &getForward() const;

    void setForward(const glm::vec3 &forward);

protected:
    glm::vec3 position;
    glm::vec3 forward;
};


#endif //GFXFRAMEWORK_WOTGAMEOBJECT_H
