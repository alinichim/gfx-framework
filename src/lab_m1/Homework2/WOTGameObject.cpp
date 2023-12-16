//
// Created by alini on 12/14/2023.
//

#include "WOTGameObject.h"

WOTGameObject::WOTGameObject(const glm::vec3 &position, const glm::vec3 &forward) : position(
        position), forward(forward) {}

glm::vec3 WOTGameObject::getPosition() {
    return position;
}

void WOTGameObject::setPosition(glm::vec3 position) {
    WOTGameObject::position = position;
}

glm::vec3 WOTGameObject::getForward() {
    return forward;
}

void WOTGameObject::setForward(glm::vec3 forward) {
    WOTGameObject::forward = forward;
}

WOTGameObject::WOTGameObject() : position(glm::vec3(0)), forward(glm::vec3(0, 0, 1)) {}
