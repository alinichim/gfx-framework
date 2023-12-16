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

bool TankShell::collision(glm::vec3 point) {
    return glm::abs(glm::dot(point - position, point - position)) <= 0.3f;
}

bool TankShell::collisionCallback(Building building) {
    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, -building.getPosition());
    glm::vec3 spos = glm::vec3(modelMatrix * glm::vec4(position, 1));
    float hx = building.getHx();
    float hy = building.getHy();
    float hz = building.getHz();
    return spos.x >= -hx && spos.x <= hx && spos.y >= -hy && spos.y <= hy && spos.z >= -hz && spos.z <= hz;
}
