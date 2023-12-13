#include "Homework1object2D.h"

#include <cmath>

#include <vector>

#include "core/engine.h"
#include "lab_m1/Homework1/Homework1transform2D.h"
#include "utils/gl_utils.h"

Mesh *Homework1object2D::CreateSlot(const std::string &name, glm::vec3 center,
                                float length, glm::vec3 color) {
    float halfLength = length / 2;

    std::vector<glm::vec3> displacements = {
            glm::vec3(-halfLength, -halfLength, 0), // 0
            glm::vec3(-halfLength, halfLength, 0),  // 1
            glm::vec3(halfLength, halfLength, 0),   // 2
            glm::vec3(halfLength, -halfLength, 0),  // 3
    };

    std::vector<VertexFormat> vertices = {
            VertexFormat(center + displacements[0], color), // 0
            VertexFormat(center + displacements[1], color), // 1
            VertexFormat(center + displacements[2], color), // 2
            VertexFormat(center + displacements[3], color), // 3
    };

    Mesh *square = new Mesh(name);

    std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3,
    };

    square->InitFromData(vertices, indices);

    return square;
}

Mesh *Homework1object2D::CreateBase(const std::string &name, glm::vec3 center,
                                float width, float height, glm::vec3 color) {
    float halfWidth = width / 2;
    float halfHeight = height / 2;

    std::vector<glm::vec3> displacements = {
            glm::vec3(-halfWidth, -halfHeight, 0), // 0
            glm::vec3(-halfWidth, halfHeight, 0),  // 1
            glm::vec3(halfWidth, halfHeight, 0),   // 2
            glm::vec3(halfWidth, -halfHeight, 0),  // 3
    };

    std::vector<VertexFormat> vertices = {
            VertexFormat(center + displacements[0], color), // 0
            VertexFormat(center + displacements[1], color), // 1
            VertexFormat(center + displacements[2], color), // 2
            VertexFormat(center + displacements[3], color), // 3
    };

    Mesh *rectangle = new Mesh(name);

    std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3,
    };

    rectangle->InitFromData(vertices, indices);

    return rectangle;
}

Mesh *Homework1object2D::CreateDefender(const std::string &name, glm::vec3 center,
                                    float length, glm::vec3 color) {
    float halfLength = length / 2;
    float thirdHalfLength = halfLength / 3;

    std::vector<glm::vec3> displacements = {
            // Diamond
            glm::vec3(-halfLength / 2, halfLength, 3),  // 0
            glm::vec3(0, 0, 3),                         // 1
            glm::vec3(-halfLength / 2, -halfLength, 3), // 2
            glm::vec3(-halfLength, 0, 3),               // 3

            // Rectangle
            glm::vec3(-halfLength / 2, -thirdHalfLength, 3), // 4
            glm::vec3(-halfLength / 2, thirdHalfLength, 3),  // 5
            glm::vec3(thirdHalfLength, thirdHalfLength, 3),  // 6
            glm::vec3(thirdHalfLength, -thirdHalfLength, 3), // 7
    };

    std::vector<VertexFormat> vertices = {
            // Diamond
            VertexFormat(center + displacements[0], color), // 0
            VertexFormat(center + displacements[1], color), // 1
            VertexFormat(center + displacements[2], color), // 2
            VertexFormat(center + displacements[3], color), // 3

            // Rectangle
            VertexFormat(center + displacements[4], color), // 4
            VertexFormat(center + displacements[5], color), // 5
            VertexFormat(center + displacements[6], color), // 6
            VertexFormat(center + displacements[7], color), // 7
    };

    Mesh *diamond = new Mesh(name);

    std::vector<unsigned int> indices = {
            0, 1, 2, 0, 2, 3, 4, 5, 6, 4, 6, 7,
    };

    diamond->InitFromData(vertices, indices);

    return diamond;
}

Mesh *Homework1object2D::CreateAttacker(const std::string &name, glm::vec3 center,
                                    float length, glm::vec3 colorOuter,
                                    glm::vec3 colorInner) {
    float innerLength = length * 0.70f;

    float coordinates[][2] = {
            {(float) cos(0),            (float) sin(0)},            // 0
            {(float) cos(M_PI / 3),     (float) sin(M_PI / 3)},     // 1
            {(float) cos(2 * M_PI / 3), (float) sin(2 * M_PI / 3)}, // 2
            {(float) cos(M_PI),         (float) sin(M_PI)},         // 3
            {(float) cos(4 * M_PI / 3), (float) sin(4 * M_PI / 3)}, // 4
            {(float) cos(5 * M_PI / 3), (float) sin(5 * M_PI / 3)}, // 5
    };

    std::vector<glm::vec3> displacements = {
            // Outer hexagon
            glm::vec3(length * coordinates[0][0], length * coordinates[0][1], 0),
            glm::vec3(length * coordinates[1][0], length * coordinates[1][1], 0),
            glm::vec3(length * coordinates[2][0], length * coordinates[2][1], 0),
            glm::vec3(length * coordinates[3][0], length * coordinates[3][1], 0),
            glm::vec3(length * coordinates[4][0], length * coordinates[4][1], 0),
            glm::vec3(length * coordinates[5][0], length * coordinates[5][1], 0),
            // Inner hexagon
            glm::vec3(innerLength * coordinates[0][0],
                      innerLength * coordinates[0][1], 1),
            glm::vec3(innerLength * coordinates[1][0],
                      innerLength * coordinates[1][1], 1),
            glm::vec3(innerLength * coordinates[2][0],
                      innerLength * coordinates[2][1], 1),
            glm::vec3(innerLength * coordinates[3][0],
                      innerLength * coordinates[3][1], 1),
            glm::vec3(innerLength * coordinates[4][0],
                      innerLength * coordinates[4][1], 1),
            glm::vec3(innerLength * coordinates[5][0],
                      innerLength * coordinates[5][1], 1),
    };

    std::vector<VertexFormat> vertices = {
            // Outer hexagon
            VertexFormat(center + displacements[0], colorOuter), // 0
            VertexFormat(center + displacements[1], colorOuter), // 1
            VertexFormat(center + displacements[2], colorOuter), // 2
            VertexFormat(center + displacements[3], colorOuter), // 3
            VertexFormat(center + displacements[4], colorOuter), // 4
            VertexFormat(center + displacements[5], colorOuter), // 5
            // Inner hexagon
            VertexFormat(center + displacements[6], colorInner),  // 6
            VertexFormat(center + displacements[7], colorInner),  // 7
            VertexFormat(center + displacements[8], colorInner),  // 8
            VertexFormat(center + displacements[9], colorInner),  // 9
            VertexFormat(center + displacements[10], colorInner), // 10
            VertexFormat(center + displacements[11], colorInner), // 11
    };

    std::vector<unsigned int> indices = {
            0, 1, 2, 2, 3, 4, 0, 4, 5, 0, 2, 4,
            6, 7, 8, 8, 9, 10, 6, 10, 11, 6, 8, 10,
    };

    Mesh *enemy = new Mesh(name);
    enemy->InitFromData(vertices, indices);

    return enemy;
}

Mesh *Homework1object2D::CreateStar(const std::string &name, glm::vec3 center,
                                float length, glm::vec3 color) {
    float halfLength = length / 2;
    float slice = 2 * M_PI / 5;
    float phase = M_PI / 5;
    float coordinates[][2] = {
            // Outer vertices
            {(float) cos(slice * 0),         (float) sin(slice * 0)}, // 0
            {(float) cos(slice * 1),         (float) sin(slice * 1)}, // 1
            {(float) cos(slice * 2),         (float) sin(slice * 2)}, // 2
            {(float) cos(slice * 3),         (float) sin(slice * 3)}, // 3
            {(float) cos(slice * 4),         (float) sin(slice * 4)}, // 4
            // Inner vertices
            {(float) cos(slice * 0 + phase), (float) sin(slice * 0 + phase)}, // 5
            {(float) cos(slice * 1 + phase), (float) sin(slice * 1 + phase)}, // 6
            {(float) cos(slice * 2 + phase), (float) sin(slice * 2 + phase)}, // 7
            {(float) cos(slice * 3 + phase), (float) sin(slice * 3 + phase)}, // 8
            {(float) cos(slice * 4 + phase), (float) sin(slice * 4 + phase)}, // 9
    };

    std::vector<glm::vec3> displacements = {
            // Outer vertices
            glm::vec3(length * coordinates[0][0], length * coordinates[0][1], 0),
            glm::vec3(length * coordinates[1][0], length * coordinates[1][1], 0),
            glm::vec3(length * coordinates[2][0], length * coordinates[2][1], 0),
            glm::vec3(length * coordinates[3][0], length * coordinates[3][1], 0),
            glm::vec3(length * coordinates[4][0], length * coordinates[4][1], 0),
            // Inner vertices
            glm::vec3(halfLength * coordinates[5][0], halfLength * coordinates[5][1],
                      0),
            glm::vec3(halfLength * coordinates[6][0], halfLength * coordinates[6][1],
                      0),
            glm::vec3(halfLength * coordinates[7][0], halfLength * coordinates[7][1],
                      0),
            glm::vec3(halfLength * coordinates[8][0], halfLength * coordinates[8][1],
                      0),
            glm::vec3(halfLength * coordinates[9][0], halfLength * coordinates[9][1],
                      0),
    };

    std::vector<VertexFormat> vertices = {
            // Outer vertices
            VertexFormat(center + displacements[0], color), // 0
            VertexFormat(center + displacements[1], color), // 1
            VertexFormat(center + displacements[2], color), // 2
            VertexFormat(center + displacements[3], color), // 3
            VertexFormat(center + displacements[4], color), // 4
            // Inner vertices
            VertexFormat(center + displacements[5], color), // 5
            VertexFormat(center + displacements[6], color), // 6
            VertexFormat(center + displacements[7], color), // 7
            VertexFormat(center + displacements[8], color), // 8
            VertexFormat(center + displacements[9], color), // 9
    };

    std::vector<unsigned int> indices = {
            0, 5, 9, 1, 6, 5, 2, 7, 6, 3, 8, 7, 4, 9, 8, 5, 6, 7, 5, 7, 9, 7, 8, 9,
    };

    Mesh *star = new Mesh(name);
    star->InitFromData(vertices, indices);

    return star;
}

Mesh *Homework1object2D::CreateHUDSlot(const std::string &name, glm::vec3 center,
                                   float length, glm::vec3 borderColor) {
    std::vector<glm::vec3> displacements = {
            glm::vec3(length / 2, length / 2, 0),
            glm::vec3(length / 2, -length / 2, 0),
            glm::vec3(-length / 2, -length / 2, 0),
            glm::vec3(-length / 2, length / 2, 0),
    };

    std::vector<VertexFormat> vertices = {
            VertexFormat(center + displacements[0], borderColor), // 0
            VertexFormat(center + displacements[1], borderColor), // 1
            VertexFormat(center + displacements[2], borderColor), // 2
            VertexFormat(center + displacements[3], borderColor), // 3
    };

    std::vector<unsigned int> indices = {0, 1, 2, 3};

    Mesh *hudSlot = new Mesh(name);
    hudSlot->SetDrawMode(GL_LINE_LOOP);
    hudSlot->InitFromData(vertices, indices);

    return hudSlot;
}

glm::mat3 Homework1object2D::AttackerMoveAnimation(float delta) {

    return Homework1transform2D::Translate(-delta * 10, 0);
}

glm::mat3 Homework1object2D::ProjectileMoveAnimation(float deltaTime, float deltaX, float deltaY) {

    glm::mat3 result = glm::mat3(1);

    // Translation
    result *= Homework1transform2D::Translate(-deltaTime * 50, 0);

    // Rotation
    result *= Homework1transform2D::Rotate(deltaTime);

    return result;
}
