//
// Created by alinichim on 11/18/23.
//

#include "ActiveGameObject.h"

ActiveGameObject::ActiveGameObject() : hp(0), color(glm::vec3(0)) {}

int ActiveGameObject::getHp() const {
    return hp;
}

void ActiveGameObject::setHp(int hp) {
    this->hp = hp;
}

const glm::vec3 &ActiveGameObject::getColor() const {
    return color;
}

void ActiveGameObject::setColor(const glm::vec3 &color) {
    this->color = color;
}
