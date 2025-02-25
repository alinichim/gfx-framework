//
// Created by alinichim on 11/18/23.
//

#include "HUDSlot.h"

Mesh *HUDSlot::getMesh() {

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
            0, 1, 2, 3
    };

    Mesh *mesh = new Mesh(name);
    mesh->SetDrawMode(GL_LINE_LOOP);
    mesh->InitFromData(vertices, indices);

    return mesh;
}

HUDSlot::HUDSlot(float side, int price) : GameSlot(side), price(price) {}

int HUDSlot::getPrice() const {
    return price;
}

void HUDSlot::setPrice(int price) {
    this->price = price;
}
