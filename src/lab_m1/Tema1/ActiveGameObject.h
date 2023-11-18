//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_ACTIVEGAMEOBJECT_H
#define GFXFRAMEWORK_ACTIVEGAMEOBJECT_H

#include "GameObject.h"

class ActiveGameObject : public GameObject {

public:
    ActiveGameObject();

    int getHp() const;

    void setHp(int hp);

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

protected:
    int hp;
    glm::vec3 color;
};


#endif //GFXFRAMEWORK_ACTIVEGAMEOBJECT_H
