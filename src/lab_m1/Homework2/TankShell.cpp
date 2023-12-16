//
// Created by alini on 12/15/2023.
//

#include "TankShell.h"

float TankShell::getRotationX() {
    return rotation_x;
}

void TankShell::setRotationX(float rotationX) {
    rotation_x = rotationX;
}

float TankShell::getRotationY() {
    return rotation_y;
}

void TankShell::setRotationY(float rotationY) {
    rotation_y = rotationY;
}

glm::vec3 TankShell::getSpeed() {
    return speed;
}

void TankShell::setSpeed(glm::vec3 speed) {
    TankShell::speed = speed;
}
