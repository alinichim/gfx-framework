//
// Created by alinichim on 11/17/23.
//

#include "BoardSlot.h"

BoardSlot::BoardSlot() {}

Mesh *BoardSlot::getMesh() {

    float halfWidth = width / 2;
    float halfHeight = height / 2;

    std::vector<glm::vec3> offsets = {
            glm::vec3(halfWidth, halfHeight, z),    // 0
            glm::vec3(-halfWidth, halfHeight, z),   // 1
            glm::vec3(-halfWidth, -halfHeight, z),  // 2
            glm::vec3(halfWidth, -halfHeight, z),   // 3
    };

    std::vector<VertexFormat> vertices;
    for (auto offset: offsets) {
        vertices.push_back(VertexFormat(center + offset, color));
    }

    std::vector<unsigned int> indices = {
            0, 1, 2, 0, 1, 3
    };

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}
