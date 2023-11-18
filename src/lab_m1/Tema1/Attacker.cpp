//
// Created by alinichim on 11/18/23.
//

#include "Attacker.h"

Attacker::Attacker() : speed(0.0f), radius(0.0f) {}

float Attacker::getSpeed() const {
    return speed;
}

void Attacker::setSpeed(float speed) {
    Attacker::speed = speed;
}

float Attacker::getRadius() const {
    return radius;
}

void Attacker::setRadius(float radius) {
    Attacker::radius = radius;
}

Mesh *Attacker::getMesh() {

    const float pRadius = 0.7f * radius;
    const float p = M_PI / 3;

    std::vector<glm::vec3> offsets;
    for (int i = 0; i < 6; ++i) {
        offsets.push_back(glm::vec3(radius * cos(i * p), radius * sin(i * p), z));
    }
    offsets.push_back(center);
    for (int i = 0; i < 6; ++i) {
        offsets.push_back(glm::vec3(pRadius * cos(i * p), pRadius * sin(i * p), z));
    }
    offsets.push_back(center);

    std::vector<VertexFormat> vertices;
    for (int i = 0; i < offsets.size() / 2; ++i) {
        vertices.push_back(VertexFormat(center + offsets[i], color));
    }
    for (int i = offsets.size() / 2; i < offsets.size(); ++i) {
        vertices.push_back(VertexFormat(center + offsets[i], glm::vec3(1, 1, 1) - color));
    }

    std::vector<unsigned int> indices = {
            0, 1, 12,
            1, 2, 12,
            2, 3, 12,
            3, 4, 12,
            4, 5, 12,
            5, 6, 12,
            6, 7, 13,
            7, 8, 13,
            8, 9, 13,
            9, 10, 13,
            10, 11, 13,
            11, 6, 13,
    };

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;

}
