//
// Created by alini on 12/14/2023.
//

#include "WOTGameObject.h"

WOTGameObject::WOTGameObject(const glm::vec3 &position, const glm::vec3 &forward, float collisionMargin) : position(
        position), forward(forward), collision_range(collisionMargin) {}

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

float WOTGameObject::getCollisionRange() const {
    return collision_range;
}

void WOTGameObject::setCollisionRange(float collisionRange) {
    collision_range = collisionRange;
}

bool WOTGameObject::collision(WOTGameObject object) {
    float margin = object.getCollisionRange() + collision_range;
    margin -= glm::distance(object.getPosition(), position);
    return (margin > 0) && (margin < 0.05f);
}

WOTGameObject::WOTGameObject() : position(glm::vec3(0)), collision_range(0), forward(glm::vec3(0, 0, 1)) {}
