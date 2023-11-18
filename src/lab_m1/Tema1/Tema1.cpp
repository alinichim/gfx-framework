#include "lab_m1/Tema1/Tema1.h"

#include "BoardBase.h"
#include "GamePoint.h"

#include "lab_m1/Tema1/Tema1object2D.h"
#include "lab_m1/Tema1/Tema1transform2D.h"

#include <iostream>

using namespace std;
using namespace m1;

Tema1::~Tema1() = default;

void Tema1::Init() {
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float) resolution.x, 0, (float) resolution.y, 0.01f,
                            400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 center = glm::vec3(0, 0, 0);

    // Add board base to meshes
    boardBase = BoardBase(BOARDBASE_WIDTH, 0.0f);
    boardBase.setHeight(GAMESLOT_SIDE * 3 + SLOT_PADDING * 2);
    boardBase.setCenter(center);
    boardBase.setColor(glm::vec3(1, 0, 0));  // red color
    boardBase.setName("boardBase");
    AddMeshToList(boardBase.getMesh());

    // Add board slots to meshes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            BoardSlot newSlot(GAMESLOT_SIDE);
            newSlot.setCenter(center);
            newSlot.setColor(glm::vec3(0, 1, 0));  // green color
            newSlot.setName("boardSlot");
            boardSlots.push_back(newSlot);
        }
    }
    AddMeshToList(boardSlots[0].getMesh());

    // Add HUD slots to meshes
    HUDSlot newSlot(GAMESLOT_SIDE, 1);
    newSlot.setCenter(center);
    newSlot.setName("hudSlot");
    newSlot.setColor(glm::vec3(1, 1, 1));  // white color
    hudSlots.push_back(newSlot);
    newSlot.setPrice(2);
    hudSlots.push_back(newSlot);
    newSlot.setPrice(2);
    hudSlots.push_back(newSlot);
    newSlot.setPrice(3);
    hudSlots.push_back(newSlot);
    AddMeshToList(hudSlots[0].getMesh());

    // Add Defenders prices
    gamePoint.setRadius(GAMEPOINT_RADIUS);
    gamePoint.setCenter(center);
    gamePoint.setColor(glm::vec3(0.15f, 0.15f, 0.15f));  // grey color
    gamePoint.setName("defenderPrice");
    AddMeshToList(gamePoint.getMesh());

    // Add HUD health bar to meshes
    hudHealthBar.setHp(3);
    hudHealthBar.setSide(GAMESLOT_SIDE);
    hudHealthBar.setPoints(2);
    hudHealthBar.setCenter(center);
    hudHealthBar.setColor(glm::vec3(1, 0, 0));  // red color
    hudHealthBar.setName("healthBar");
    hudHealthBar.setPadding(SLOT_PADDING);
    AddMeshToList(hudHealthBar.getMesh());
}

void Tema1::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {

    // Viewport
    glm::ivec2 resolution = window->GetResolution();

    glm::mat3 modelMatrix(1);
    float translateX = 0.0f;
    float translateY = 0.0f;
    float scale = 0.0f;

    // Render board base
    modelMatrix = glm::mat3(1);
    translateX = boardBase.getWidth() / 2 + BOARDBASE_LEFT_PADDING;
    translateY = boardBase.getHeight() / 2 + FOOTER_PADDING;
    boardBase.setX(translateX);
    boardBase.setY(translateY);
    modelMatrix *= Tema1transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes[boardBase.getName()], shaders["VertexColor"], modelMatrix);

    // Render board slots
    modelMatrix = glm::mat3(1);
    translateX = boardSlots[0].getSide() / 2 + BOARDBASE_LEFT_PADDING + boardBase.getWidth() + SLOT_PADDING;
    translateY = boardSlots[0].getSide() / 2 + FOOTER_PADDING;
    for (auto &slot: boardSlots) {
        slot.setX(translateX);
        slot.setY(translateY);
    }
    modelMatrix *= Tema1transform2D::Translate(translateX, translateY);
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            glm::mat3 tempModelMatrix = modelMatrix;
            translateX = (float) j * (boardSlots[0].getSide() + SLOT_PADDING);
            translateY = (float) i * (boardSlots[0].getSide() + SLOT_PADDING);
            boardSlots[i * 3 + j].setX(boardSlots[i * 3 + j].getX() + translateX);
            boardSlots[i * 3 + j].setY(boardSlots[i * 3 + j].getY() + translateY);
            tempModelMatrix *= Tema1transform2D::Translate(translateX, translateY);
            RenderMesh2D(meshes[boardSlots[0].getName()], shaders["VertexColor"], tempModelMatrix);
        }
    }

    // Render HUD slots
    modelMatrix = glm::mat3(1);
    translateX = hudSlots[0].getSide() / 2 + BOARDBASE_LEFT_PADDING;
    translateY = (float) resolution.y - hudSlots[0].getSide() / 2 - FOOTER_PADDING;
    for (auto &slot: hudSlots) {
        slot.setX(translateX);
        slot.setY(translateY);
    }
    modelMatrix *= Tema1transform2D::Translate(translateX, translateY);
    for (int i = 0; i < 4; i++) {
        glm::mat3 tempModelMatrix = modelMatrix;
        translateX = (float) i * (hudSlots[0].getSide() + SLOT_PADDING);
        hudSlots[i].setX(hudSlots[i].getX() + translateX);
        tempModelMatrix *= Tema1transform2D::Translate(translateX, 0);
        RenderMesh2D(meshes[hudSlots[0].getName()], shaders["VertexColor"], tempModelMatrix);
    }
    // Render Defender prices
    for (int i = 0; i < 4; i++) {
        modelMatrix = Tema1transform2D::Translate(hudSlots[i].getX(), hudSlots[i].getY());
        translateX = -hudSlots[i].getSide() / 2 + gamePoint.getRadius();
        translateY = -hudSlots[i].getSide() / 2 - gamePoint.getRadius();
        modelMatrix *= Tema1transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        if (i > 0) {
            modelMatrix *= Tema1transform2D::Translate(gamePoint.getRadius() * 2.0f, 0);
            RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        }
        if (i > 2) {
            modelMatrix *= Tema1transform2D::Translate(gamePoint.getRadius() * 2.0f, 0);
            RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        }
    }

    // Render health bar
    translateX = hudSlots[3].getX() + GAMESLOT_SIDE + SLOT_PADDING;
    translateY = hudSlots[3].getY();
    hudHealthBar.setX(translateX);
    hudHealthBar.setY(translateY);
    modelMatrix = Tema1transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes[hudHealthBar.getName()], shaders["VertexColor"], modelMatrix);
    // Render collected points
    translateX = hudHealthBar.getX() - GAMESLOT_SIDE / 2 + gamePoint.getRadius();
    translateY = hudHealthBar.getY() - GAMESLOT_SIDE / 2 - gamePoint.getRadius();
    modelMatrix = Tema1transform2D::Translate(translateX, translateY);
    for (int i = 0; i < hudHealthBar.getPoints(); i++) {
        modelMatrix *= Tema1transform2D::Translate(gamePoint.getRadius() * 2.0f * (float) i, 0);
        RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
    }
}

void Tema1::FrameEnd() {}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Tema1::OnInputUpdate(float deltaTime, int mods) {}

void Tema1::OnKeyPress(int key, int mods) {
    // Add key press event
}

void Tema1::OnKeyRelease(int key, int mods) {
    // Add key release event
}

void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event
}

void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}

Tema1::Tema1() = default;
