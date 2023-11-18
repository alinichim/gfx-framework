//
// Created by alinichim on 11/18/23.
//

#include "HUDHealthBar.h"

HUDHealthBar::HUDHealthBar(int hp, int points, const glm::vec3 pointsColor, float side, float padding) : hp(hp),
                                                                                                         points(points),
                                                                                                         pointsColor(
                                                                                                                 pointsColor),
                                                                                                         side(side),
                                                                                                         padding(padding) {}

int HUDHealthBar::getHp() const {
    return hp;
}

void HUDHealthBar::setHp(int hp) {
    this->hp = hp;
}

int HUDHealthBar::getPoints() const {
    return points;
}

void HUDHealthBar::setPoints(int points) {
    this->points = points;
}

const glm::vec3 &HUDHealthBar::getPointsColor() const {
    return pointsColor;
}

void HUDHealthBar::setPointsColor(const glm::vec3 &pointsColor) {
    this->pointsColor = pointsColor;
}

float HUDHealthBar::getSide() const {
    return side;
}

void HUDHealthBar::setSide(float side) {
    this->side = side;
}

Mesh *HUDHealthBar::getMesh() {

    const float halfSide = side / 2;

    std::vector<glm::vec3> offsets;
    for (int i = 0; i < hp; ++i) {
        offsets.push_back(glm::vec3(halfSide + i * (padding + side), halfSide, z));
        offsets.push_back(glm::vec3(-halfSide + i * (padding + side), halfSide, z));
        offsets.push_back(glm::vec3(-halfSide + i * (padding + side), -halfSide, z));
        offsets.push_back(glm::vec3(halfSide + i * (padding + side), -halfSide, z));
    }

    std::vector<VertexFormat> vertices;
    for (auto offset: offsets) {
        vertices.push_back(VertexFormat(center + offset, color));
    }

    std::vector<unsigned int> indices;
    for (int i = 0; i < hp; ++i) {
        indices.push_back(i * 4 + 0);
        indices.push_back(i * 4 + 1);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 0);
        indices.push_back(i * 4 + 2);
        indices.push_back(i * 4 + 3);
    }

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}

float HUDHealthBar::getPadding() const {
    return padding;
}

void HUDHealthBar::setPadding(float padding) {
    this->padding = padding;
}
