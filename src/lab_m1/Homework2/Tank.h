//
// Created by alini on 12/14/2023.
//

#ifndef GFXFRAMEWORK_TANK_H
#define GFXFRAMEWORK_TANK_H

#include "lab_m1/Homework2/WOTGameObject.h"

class Tank : public WOTGameObject {
public:
    Tank(const glm::vec3 &position, const glm::vec3 &forward, float collisionMargin);

    Tank();

    void Move(float distance);

    void Steer(float angle);

    void Aim(float angle_x, float angle_y);

    float getGunRotationX() const;

    void setGunRotationX(float gunRotationX);

    float getGunRotationY() const;

    void setGunRotationY(float gunRotationY);

    float getTurretRotationY() const;

    void setTurretRotationY(float turretRotationY);

    const glm::vec3 &getGunCenter() const;

    void setGunCenter(const glm::vec3 &gunCenter);

    int getHp() const;

    void setHp(int hp);

    float getSpeed() const;

    void setSpeed(float speed);

    float getBodyRotationY() const;

    void setBodyRotationY(float bodyRotationY);

protected:
    float body_rotation_y = 0;
    float gun_rotation_x = 0;
    float gun_rotation_y = 0;
    float turret_rotation_y = 0;
    glm::vec3 gun_center = glm::vec3(0.119408f, 2.1954, 1.01288f);
    int hp = 3;
    float speed = 1;
};


#endif //GFXFRAMEWORK_TANK_H
