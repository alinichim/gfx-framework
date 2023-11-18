//
// Created by alinichim on 11/18/23.
//

#include "GamePoint.h"

GamePoint::GamePoint(float radius) : radius(radius) {}

float GamePoint::getRadius() const {
    return radius;
}

void GamePoint::setRadius(float radius) {
    this->radius = radius;
}

std::vector<glm::vec3> GamePoint::getOffsets() {

    const float halfRadius = radius / 2;
    const float p1 = 2 * M_PI / 5;
    const float p2 = M_PI / 5;

    std::vector<glm::vec3> offsets;
    for (int i = 0; i < 5; i++) {
        offsets.push_back(glm::vec3(radius * cos(i * p1), radius * sin(i * p1), z));
        offsets.push_back(glm::vec3(halfRadius * cos(i * p1 + p2), halfRadius * sin(i * p1 + p2), z));
    }

    return offsets;
}

Mesh *GamePoint::getMesh() {

    const float halfRadius = radius / 2;
    const float p1 = 2 * M_PI / 5;
    const float p2 = M_PI / 5;

    std::vector<glm::vec3> offsets = getOffsets();

    std::vector<VertexFormat> vertices;
    for (auto offset: offsets) {
        vertices.push_back(VertexFormat(center + offset, color));
    }

    std::vector<unsigned int> indices = {
            0, 1, 9,
            1, 2, 3,
            3, 4, 5,
            5, 6, 7,
            7, 8, 9,
            1, 3, 7,
            3, 5, 7,
            1, 7, 9,
    };

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}
