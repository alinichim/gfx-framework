//
// Created by alinichim on 11/18/23.
//

#include "Defender.h"

Defender::Defender() : fireRate(1.5f), length(0.0f), deltaTime(0.0f) {
    Defender::hp = 1;
}


float Defender::getFireRate() const {
    return fireRate;
}

void Defender::setFireRate(float fireRate) {
    Defender::fireRate = fireRate;
}

float Defender::getLength() const {
    return length;
}

void Defender::setLength(float length) {
    Defender::length = length;
}

Mesh *Defender::getMesh() {

    const float halfLength = length / 2;
    const float thirdHalfLength = halfLength / 3;

    std::vector<glm::vec3> offsets = {
            glm::vec3(0.0f, length, z),
            glm::vec3(-halfLength, 0.0f, z),
            glm::vec3(0.0f, -length, z),
            glm::vec3(halfLength, 0.0f, z),
            glm::vec3(0.0f, -thirdHalfLength, z),
            glm::vec3(0.0f, thirdHalfLength, z),
            glm::vec3(length, thirdHalfLength, z),
            glm::vec3(length, -thirdHalfLength, z),
    };

    std::vector<VertexFormat> vertices;
    for (auto offset: offsets) {
        vertices.push_back(VertexFormat(center + offset, color));
    }

    std::vector<unsigned int> indices = {
            0, 1, 2,
            0, 2, 3,
            6, 5, 4,
            6, 4, 7,
    };

    Mesh *mesh = new Mesh(name);
    mesh->InitFromData(vertices, indices);

    return mesh;
}

Defender::Defender(float fireRate, float length, float deltaTime) : fireRate(fireRate), length(length),
                                                                    deltaTime(deltaTime) {}

float Defender::getDeltaTime() const {
    return deltaTime;
}

void Defender::setDeltaTime(float deltaTime) {
    Defender::deltaTime = deltaTime;
}
