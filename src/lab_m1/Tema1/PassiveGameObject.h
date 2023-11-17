//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_PASSIVEGAMEOBJECT_H
#define GFXFRAMEWORK_PASSIVEGAMEOBJECT_H

#include "GameObject.h"

class PassiveGameObject : public GameObject {
public:
    PassiveGameObject();
    
    PassiveGameObject(const glm::vec3 &color, float width, float height);

    ~PassiveGameObject();

    const glm::vec3 &getColor() const;

    void setColor(const glm::vec3 &color);

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

protected:
    glm::vec3 color;
    float width;
    float height;
};


#endif //GFXFRAMEWORK_PASSIVEGAMEOBJECT_H
