#include "lab_m1/Tema1/Tema1.h"

#include "lab_m1/Tema1/Tema1object2D.h"
#include "lab_m1/Tema1/Tema1transform2D.h"

using namespace std;
using namespace m1;

Tema1::Tema1() = default;

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

    // Board
    Mesh *boardSlot =
            Tema1object2D::CreateSlot("slot", center, slot_side, glm::vec3(0, 1, 0));
    AddMeshToList(boardSlot);
    Mesh *boardBase = Tema1object2D::CreateBase("boardBase", center, base_width,
                                                base_height, glm::vec3(1, 0, 0));
    AddMeshToList(boardBase);

    // HUD
    Mesh *hudSlot = Tema1object2D::CreateHUDSlot(
            "hudSlot", center, slot_side, glm::vec3(1, 1, 1), glm::vec3(0, 0, 1));
    AddMeshToList(hudSlot);
    Mesh *healthPoint = Tema1object2D::CreateSlot("healthPoint", center, slot_side, glm::vec3(1, 0, 0));
    AddMeshToList(healthPoint);

    // Add model matrices
    modelMatrix = glm::mat3(1);
    modelMatrix *= Tema1transform2D::Translate(slot_side / 2, slot_side / 2);
    modelMatrix *= Tema1transform2D::Translate(base_left_padding, footer_padding);
    modelMatrix *= Tema1transform2D::Translate(base_width / 2 + slot_side / 2, 0);
    modelMatrix *= Tema1transform2D::Translate(slot_padding, 0);
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        glm::mat3 slotPosition = modelMatrix;
        slotPosition *=
                Tema1transform2D::Translate((slot_side + slot_padding) * (float) col,
                                            (slot_side + slot_padding) * (float) row);
        slots.push_back(slotPosition);
    }
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(
                slot_side / 2, (float) window->GetResolution().y - slot_side / 2);
        modelMatrix *= Tema1transform2D::Translate(10, -10);
        modelMatrix *= Tema1transform2D::Translate((float) i * (slot_side + 10), 0);
        hudSlots.push_back(modelMatrix);
    }
    for (int i = 4; i < 7; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(
                slot_side / 2, (float) window->GetResolution().y - slot_side / 2);
        modelMatrix *= Tema1transform2D::Translate(10, -10);
        modelMatrix *= Tema1transform2D::Translate((float) i * (slot_side + 10), 0);
        healthPoints.push_back(modelMatrix);
    }
    base = glm::mat3(1);
    base *= Tema1transform2D::Translate(base_width / 2, base_height / 2);
    base *= Tema1transform2D::Translate(base_left_padding, footer_padding);

}

void Tema1::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.1f, 0.1f, 0.1f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Tema1::Update(float deltaTimeSeconds) {
    // Game board
    RenderMesh2D(meshes["boardBase"], shaders["VertexColor"], base);
    for (int i = 0; i < 9; i++) {
        RenderMesh2D(meshes["slot"], shaders["VertexColor"], slots[i]);
    }

    // HUD
    // Render HUD slots
    for (int i = 0; i < 4; i++) {
        RenderMesh2D(meshes["hudSlot"], shaders["VertexColor"], hudSlots[i]);
    }
    // Render health points
    for (int i = 0; i < 3; i++) {
        RenderMesh2D(meshes["healthPoint"], shaders["VertexColor"], healthPoints[i]);
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
    // Add mouse button press event
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}
