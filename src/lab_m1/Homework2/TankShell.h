//
// Created by alini on 12/15/2023.
//

#ifndef GFXFRAMEWORK_TANKSHELL_H
#define GFXFRAMEWORK_TANKSHELL_H

#include "lab_m1/Homework2/WOTGameObject.h"
#include "Building.h"

class TankShell : public WOTGameObject {

public:
    float getRotationX();

    void setRotationX(float rotationX);

    float getRotationY();

    void setRotationY(float rotationY);

    glm::vec3 getSpeed();

    void setSpeed(glm::vec3 speed);

    bool collision(glm::vec3 point) override;

    bool collisionCallback(Building building);

protected:
    float rotation_x = 0;
    float rotation_y = 0;
    glm::vec3 speed;
};


#endif //GFXFRAMEWORK_TANKSHELL_H
