//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_PASSIVEGAMEOBJECT_H
#define GFXFRAMEWORK_PASSIVEGAMEOBJECT_H

#include "GameObject.h"

class PassiveGameObject : public GameObject {
public:
    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

protected:
    glm::vec3 color;
};


#endif //GFXFRAMEWORK_PASSIVEGAMEOBJECT_H
