//
// Created by alinichim on 11/17/23.
//

#include "BoardSlot.h"


Mesh *BoardSlot::getMesh() {

    float halfSide = side / 2;

    std::vector<glm::vec3> offsets = {
            glm::vec3(halfSide, halfSide, z),   // 0
            glm::vec3(-halfSide, halfSide, z),  // 1
            glm::vec3(-halfSide, -halfSide, z), // 2
            glm::vec3(halfSide, -halfSide, z),  // 3
    };

    std::vector<VertexFormat> vertices;
    for (auto offset: offsets) {
        vertices.push_back(VertexFormat(center + offset, color));
    }

    std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3
    };

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}

BoardSlot::BoardSlot(float side) : GameSlot(side) {}
