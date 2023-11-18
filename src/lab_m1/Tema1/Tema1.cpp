#include "lab_m1/Tema1/Tema1.h"

#include "lab_m1/Tema1/Tema1object2D.h"
#include "lab_m1/Tema1/Tema1transform2D.h"

#include <iostream>

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
