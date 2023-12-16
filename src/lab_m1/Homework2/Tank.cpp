//
// Created by alini on 12/14/2023.
//

#include "Tank.h"

float Tank::getGunRotationX() const {
    return gun_rotation_x;
}

void Tank::setGunRotationX(float gunRotationX) {
    gun_rotation_x = gunRotationX;
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

Tank::Tank(const glm::vec3 &position, const glm::vec3 &forward, float collisionMargin) {}

Tank::Tank() : WOTGameObject() {

}

void Tank::Move(float distance) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    position += dir * distance * speed;
}

float Tank::getSpeed() const {
    return speed;
}

void Tank::setSpeed(float speed) {
    Tank::speed = speed;
}

void Tank::Steer(float angle) {
    body_rotation_y += angle;
    glm::vec4 newVector =
            glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) *
            glm::vec4(forward, 1);
    forward = glm::normalize(glm::vec3(newVector));
}

float Tank::getBodyRotationY() const {
    return body_rotation_y;
}

void Tank::setBodyRotationY(float bodyRotationY) {
    body_rotation_y = bodyRotationY;
}
