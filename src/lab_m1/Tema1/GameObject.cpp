//
// Created by alinichim on 11/17/23.
//

#include "GameObject.h"
#include "components/simple_scene.h"

#include <string>

#define DEFAULT_GAMEOBJECT_NAME "NONAME"

GameObject::GameObject() : scale(1.0f), angle(0.0f), x(0.0f), y(0.0f), z(0.0f), name(DEFAULT_GAMEOBJECT_NAME),
                           center(glm::vec3(0)) {}

GameObject::GameObject(float scale, float angle, float x, float y, float z,
                       const std::string name, const glm::vec3 center) : scale(scale), angle(angle), x(x), y(y), z(z),
                                                                         name(name), center(center) {}

GameObject::~GameObject() = default;

float GameObject::getScale() const {
    return scale;
}

void GameObject::setScale(float scale) {
    this->scale = scale;
}

float GameObject::getAngle() const {
    return angle;
}

void GameObject::setAngle(float angle) {
    this->angle = angle;
}

float GameObject::getX() const {
    return x;
}

void GameObject::setX(float x) {
    this->x = x;
}

float GameObject::getY() const {
    return y;
}

void GameObject::setY(float y) {
    this->y = y;
}

float GameObject::getZ() const {
    return z;
}

void GameObject::setZ(float z) {
    this->z = z;
}

const std::string &GameObject::getName() const {
    return name;
}

void GameObject::setName(const std::string &name) {
    this->name = name;
}

const glm::vec3 &GameObject::getCenter() const {
    return center;
}

void GameObject::setCenter(const glm::vec3 &center) {
    this->center = center;
}
