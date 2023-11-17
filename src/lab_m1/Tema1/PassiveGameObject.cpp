//
// Created by alinichim on 11/17/23.
//

#include "PassiveGameObject.h"

PassiveGameObject::PassiveGameObject() {}

PassiveGameObject::PassiveGameObject(const glm::vec3 &color, float width, float height) : color(color), width(width),
                                                                                          height(height) {}

PassiveGameObject::~PassiveGameObject() {

}

const glm::vec3 &PassiveGameObject::getColor() const {
    return color;
}

void PassiveGameObject::setColor(const glm::vec3 &color) {
    PassiveGameObject::color = color;
}

float PassiveGameObject::getWidth() const {
    return width;
}

void PassiveGameObject::setWidth(float width) {
    PassiveGameObject::width = width;
}

float PassiveGameObject::getHeight() const {
    return height;
}

void PassiveGameObject::setHeight(float height) {
    PassiveGameObject::height = height;
}
