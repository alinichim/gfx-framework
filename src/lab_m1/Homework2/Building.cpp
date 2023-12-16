//
// Created by alini on 12/16/2023.
//

#include "Building.h"

float Building::getHx() {
    return hx;
}

void Building::setHx(float hx) {
    Building::hx = hx;
}

float Building::getHy() {
    return hy;
}

void Building::setHy(float hy) {
    Building::hy = hy;
}

float Building::getHz() {
    return hz;
}

void Building::setHz(float hz) {
    Building::hz = hz;
}

bool Building::collision(glm::vec3 point) {
    return glm::distance(point, position) < std::max(hx, hz);
}
