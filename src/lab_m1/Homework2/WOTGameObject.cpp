//
// Created by alini on 12/14/2023.
//

#include "WOTGameObject.h"

WOTGameObject::WOTGameObject(const glm::vec3 &position, const glm::vec3 &forward) : position(
        position), forward(forward) {}

const glm::vec3 &WOTGameObject::getPosition() const {
    return position;
}

void WOTGameObject::setPosition(const glm::vec3 &position) {
    WOTGameObject::position = position;
}

const glm::vec3 &WOTGameObject::getForward() const {
    return forward;
}

void WOTGameObject::setForward(const glm::vec3 &forward) {
    WOTGameObject::forward = forward;
}

WOTGameObject::WOTGameObject() : position(glm::vec3(0)), forward(glm::vec3(0, 0, 1)) {}
