//
// Created by alinichim on 11/17/23.
//

#include "PassiveGameObject.h"

#include "components/simple_scene.h"

const glm::vec3 &PassiveGameObject::getColor() const {
    return color;
}

void PassiveGameObject::setColor(const glm::vec3 &color) {
    PassiveGameObject::color = color;
}
