//
// Created by alini on 12/14/2023.
//

#ifndef GFXFRAMEWORK_TANK_H
#define GFXFRAMEWORK_TANK_H

#include "lab_m1/Homework2/WOTGameObject.h"
#include "Building.h"

class Tank : public WOTGameObject {
public:
    Tank(const glm::vec3 &position, const glm::vec3 &forward, float collisionMargin);

    Tank();

    void Move(float distance);

    void Steer(float angle);

    bool collision(glm::vec3 point) override;

    bool collision(Building building);

    /**
     * Callback function for tank-tank collision
     * @param tank
     * @return The offset to the next position of the calling tank
     */
    glm::vec3 collisionCallback(Tank &tank);

    glm::vec3 collisionCallback(Building &building);

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

    float getProjectileSpeed();

    void setProjectileSpeed(float projectileSpeed);

    float getRadius();

    void setRadius(float radius);

protected:
    float body_rotation_y = 0;
    float gun_rotation_x = 0;
    float gun_rotation_y = 0;
    float turret_rotation_y = 0;
    glm::vec3 gun_center = glm::vec3(0.119408f, 2.1954, 1.01288f);
    int hp = 3;
    float speed = 3;
    float projectileSpeed = 8;
    float radius = 3;
};


#endif //GFXFRAMEWORK_TANK_H
