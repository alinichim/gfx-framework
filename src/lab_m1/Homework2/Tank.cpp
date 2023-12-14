//
// Created by alini on 12/14/2023.
//

#include "Tank.h"

float clamp_rotation(float x, float min=-M_PI / 4, float max=M_PI / 8) {
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    }
    return x;
}

float Tank::getGunRotationX() const {
    return clamp_rotation(gun_rotation_x);
}

void Tank::setGunRotationX(float gunRotationX) {
    gun_rotation_x = clamp_rotation(gunRotationX);
}

float Tank::getGunRotationY() const {
    return gun_rotation_y;
}

void Tank::setGunRotationY(float gunRotationY) {
    gun_rotation_y = gunRotationY;
}

float Tank::getTurretRotationY() const {
    return turret_rotation_y;
}

void Tank::setTurretRotationY(float turretRotationY) {
    turret_rotation_y = turretRotationY;
}

const glm::vec3 &Tank::getGunCenter() const {
    return gun_center;
}

void Tank::setGunCenter(const glm::vec3 &gunCenter) {
    gun_center = gunCenter;
}

int Tank::getHp() const {
    return hp;
}

void Tank::setHp(int hp) {
    Tank::hp = hp;
}
