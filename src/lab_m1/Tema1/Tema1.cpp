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

    logicSpace.x = 0;
    logicSpace.y = 0;
    logicSpace.width = (float) resolution.x;
    logicSpace.height = (float) resolution.y;

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
            "hudSlot", center, slot_side, glm::vec3(1, 1, 1));
    AddMeshToList(hudSlot);
    Mesh *healthPoint = Tema1object2D::CreateSlot("healthPoint", center, slot_side, glm::vec3(1, 0, 0));
    AddMeshToList(healthPoint);

    // Attackers
    // RED attacker
    Mesh *attacker = Tema1object2D::CreateAttacker("attacker" + std::to_string(ColorType::RED), center,
                                                   attacker_length, glm::vec3(1, 0, 0),
                                                   glm::vec3(0, 1, 1));
    AddMeshToList(attacker);
    // BLUE attacker
    attacker = Tema1object2D::CreateAttacker("attacker" + std::to_string(ColorType::BLUE), center,
                                             attacker_length, glm::vec3(0, 1, 0),
                                             glm::vec3(1, 0, 1));
    AddMeshToList(attacker);
    // YELLOW attacker
    attacker = Tema1object2D::CreateAttacker("attacker" + std::to_string(ColorType::YELLOW), center,
                                             attacker_length, glm::vec3(1, 1, 0),
                                             glm::vec3(0, 0, 1));
    AddMeshToList(attacker);
    // PURPLE attacker
    attacker = Tema1object2D::CreateAttacker("attacker" + std::to_string(ColorType::PURPLE), center,
                                             attacker_length, glm::vec3(1, 0, 1),
                                             glm::vec3(0, 1, 0));
    AddMeshToList(attacker);

    // Defender price
    Mesh *defenderPrice = Tema1object2D::CreateStar("defenderPrice", center, star_length,
                                                    glm::vec3(0.3f, 0.3f, 0.3f));
    AddMeshToList(defenderPrice);

    // Defender
    // RED defender
    Mesh *defender = Tema1object2D::CreateDefender("defender" + std::to_string(ColorType::RED), center,
                                                   defender_length, glm::vec3(1, 0, 0));
    AddMeshToList(defender);
    // PURPLE defender
    defender = Tema1object2D::CreateDefender("defender" + std::to_string(ColorType::PURPLE), center, defender_length,
                                             glm::vec3(1, 0, 1));
    AddMeshToList(defender);
    // BLUE defender
    defender = Tema1object2D::CreateDefender("defender" + std::to_string(ColorType::BLUE), center, defender_length,
                                             glm::vec3(0, 0, 1));
    AddMeshToList(defender);
    // YELLOW defender
    defender = Tema1object2D::CreateDefender("defender" + std::to_string(ColorType::YELLOW), center, defender_length,
                                             glm::vec3(1, 1, 0));
    AddMeshToList(defender);
    // Projectile
    // RED projectile
    Mesh *projectile = Tema1object2D::CreateStar("projectile" + std::to_string(ColorType::RED), center,
                                                 star_length * 2, glm::vec3(1, 0, 0));
    AddMeshToList(projectile);
    // PURPLE projectile
    projectile = Tema1object2D::CreateStar("projectile" + std::to_string(ColorType::PURPLE), center, star_length * 2,
                                           glm::vec3(1, 0, 1));
    AddMeshToList(projectile);
    // BLUE projectile
    projectile = Tema1object2D::CreateStar("projectile" + std::to_string(ColorType::BLUE), center, star_length * 2,
                                           glm::vec3(0, 0, 1));
    AddMeshToList(projectile);
    // YELLOW projectile
    projectile = Tema1object2D::CreateStar("projectile" + std::to_string(ColorType::YELLOW), center, star_length * 2,
                                           glm::vec3(1, 1, 0));
    AddMeshToList(projectile);

    // Add model matrices
    float angle, x, y;
    // Board slots
    angle = x = y = 0;
    x = base_left_padding + base_width + (slot_side / 2) + slot_padding;
    y = footer_padding + (slot_side / 2);
    for (int i = 0; i < 9; i++) {
        int row = i / 3;
        int col = i % 3;
        PositionData slotData(0, (slot_side + slot_padding) * (float) col + x,
                              (slot_side + slot_padding) * (float) row + y);
        slots.push_back(slotData);
    }
    // HUD slots
    angle = x = y = 0;
    for (int i = 0; i < 4; i++) {
        x = slot_side / 2 + 10 + (float) i * (slot_side + 10);
        y = (float) window->GetResolution().y - slot_side / 2 - 10;
        PositionData slotData(0, x, y);
        hudSlots.push_back(slotData);
    }
    // Health points
    angle = x = y = 0;
    for (int i = 0; i < 3; i++) {
        x = slot_side / 2 + 10 + (float) (i + 4) * (slot_side + 10);
        y = (float) window->GetResolution().y - slot_side / 2 - 10;
        PositionData slotData(0, x, y);
        healthPoints.push_back(slotData);
    }
    for (int i = 0; i < points.size(); i++) {
        points[i].x = 10 + (float) 4 * (slot_side + 10) + 20;
        points[i].x += (float) i * 2 * star_length;
        points[i].y = (float) window->GetResolution().y - slot_side - 10 - star_length;
    }
    // Board base
    angle = x = y = 0;
    base.x = base_width / 2 + base_left_padding;
    base.y = base_height / 2 + footer_padding;
}

void Tema1::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.5f, 0.5f, 0.5f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

glm::mat3 Tema1::VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace) {
    float sx, sy, tx, ty;
    sx = viewSpace.width / logicSpace.width;
    sy = viewSpace.height / logicSpace.height;
    tx = viewSpace.x - sx * logicSpace.x;
    ty = viewSpace.y - sy * logicSpace.y;

    return glm::transpose(glm::mat3(
            sx, 0.0f, tx,
            0.0f, sy, ty,
            0.0f, 0.0f, 1.0f));
}

void Tema1::SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear) {
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float) viewSpace.x, (float) (viewSpace.x + viewSpace.width), (float) viewSpace.y,
                                      (float) (viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void Tema1::Update(float deltaTimeSeconds) {

    // Viewport
    glm::ivec2 resolution = window->GetResolution();

    // Sets the screen area where to draw - the left half of the window
    ViewportSpace viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0), true);

    // Compute the 2D visualization matrix
    glm::mat3 visMatrix = glm::mat3(1);
    visMatrix *= VisualizationTransf2D(logicSpace, viewSpace);

    // Game board
    modelMatrix = glm::mat3(1);
    modelMatrix *= Tema1transform2D::Translate(base.x, base.y);
    RenderMesh2D(meshes["boardBase"], shaders["VertexColor"], visMatrix * modelMatrix);
    for (int i = 0; i < 9; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(slots[i].x, slots[i].y);
        RenderMesh2D(meshes["slot"], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // HUD
    // Render HUD slots
    for (int i = 0; i < 4; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(hudSlots[i].x, hudSlots[i].y);
        RenderMesh2D(meshes["hudSlot"], shaders["VertexColor"], visMatrix * modelMatrix);
        RenderMesh2D(meshes["defender" + std::to_string(i + 1)], shaders["VertexColor"], visMatrix * modelMatrix);
    }
    // Render health points
    for (int i = 0; i < 3; i++) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(healthPoints[i].x, healthPoints[i].y);
        RenderMesh2D(meshes["healthPoint"], shaders["VertexColor"], visMatrix * modelMatrix);
    }
    // Render defender prices
    modelMatrix = glm::mat3(1);
    modelMatrix *= Tema1transform2D::Translate(hudSlots[0].x, hudSlots[0].y);
    modelMatrix *= Tema1transform2D::Translate(-slot_side / 2, -slot_side / 2);
    modelMatrix *= Tema1transform2D::Translate(star_length, -star_length);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(slot_side + 10, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(2 * star_length, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(-2 * star_length, 0);
    modelMatrix *= Tema1transform2D::Translate(slot_side + 10, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(2 * star_length, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(-2 * star_length, 0);
    modelMatrix *= Tema1transform2D::Translate(slot_side + 10, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(2 * star_length, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    modelMatrix *= Tema1transform2D::Translate(2 * star_length, 0);
    RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    // Render points
    for (auto point: points) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(point.x, point.y);
        RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // Render collectable points
    pointsTimePassed += deltaTimeSeconds;
    if (pointsTimePassed >= pointsDeltaTime) {
        pointsTimePassed -= pointsDeltaTime;
        std::mt19937 gen(rd());
        std::uniform_real_distribution<float> disx(5 * slot_side, (float) resolution.x);
        std::uniform_real_distribution<float> disy(10, (float) resolution.y - slot_side - 10);
        for (int i = 0; i < 3; i++) {
            float x = disx(gen);
            float y = disy(gen);
            collectablePoints.push_back(PositionData(0, x, y));
        }
    }
    for (auto point: collectablePoints) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(point.x, point.y);
        RenderMesh2D(meshes["defenderPrice"], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // Render defenders
    for (auto defender: defenders) {
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(defender.position.x, defender.position.y);
        string defenderName = "defender" + std::to_string(defender.color);
        RenderMesh2D(meshes[defenderName], shaders["VertexColor"], visMatrix * modelMatrix);
    }

    // Render attackers
    std::mt19937 gen(rd());
    if (attackerTime <= 0) {
        std::uniform_int_distribution<int> disLane(0, 3);
        std::uniform_int_distribution<int> disColor(1, 5);
        std::uniform_real_distribution<> disAttackerTime(3.0f, 6.0f);

        // Place attacker
        int lane = disLane(gen);
        int color = disColor(gen);
        attackers.push_back(
                ObjectData(3, static_cast<ColorType>(color), PositionData(0, resolution.x + 10, slots[lane * 3].y)));

        // Set time
        attackerTime = disAttackerTime(gen);
    } else {
        attackerTime -= deltaTimeSeconds;
    }
    for (auto &attacker: attackers) {
        if (attacker.hp <= 0) {

        }
        attacker.position.x -= deltaTimeSeconds * 100.0f;
        modelMatrix = glm::mat3(1);
        modelMatrix *= Tema1transform2D::Translate(attacker.position.x, attacker.position.y);
        string attackerName = "attacker" + std::to_string(attacker.color);
        RenderMesh2D(meshes[attackerName], shaders["VertexColor"], visMatrix * modelMatrix);
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
    glm::ivec2 resolution = window->GetResolution();
    mouseY = resolution.y - mouseY;
    if (5 * slot_side <= mouseX && mouseX <= (float) resolution.x && 10 <= mouseY && mouseY <= (float) resolution.y) {
        for (int i = 0; i < collectablePoints.size(); i++) {
            if (GetDistance(collectablePoints[i].x, collectablePoints[i].y, mouseX, mouseY) <= star_length) {
                collectablePoints.erase(collectablePoints.begin() + i);
                float ny = points[points.size() - 1].y;
                float nx = points[points.size() - 1].x;
                points.push_back(PositionData(0, nx + 2 * star_length, ny));
                break;
            }
        }
    } else if (mouseX <= 5 * slot_side && mouseY <= 5 * slot_side) {
        for (auto slot: slots) {
            if (slot.x - slot_side / 2 <= mouseX && mouseX <= slot.x + slot_side / 2 &&
                slot.y - slot_side / 2 <= mouseY && mouseY <= slot.y + slot_side / 2) {
                bool found = false;
                for (int i = 0; i < defenders.size(); i++) {
                    if (defenders[i].position.x == slot.x && defenders[i].position.y == slot.y) {
                        found = true;
                        defenders.erase(defenders.begin() + i);
                        break;
                    }
                }
                if (!found && selectedDefender != NOCOL) {
                    defenders.push_back(
                            ObjectData(3, selectedDefender, (PositionData(0, slot.x, slot.y))));
                    std::cout << "Added defender" << std::endl;
                    selectedDefender = NOCOL;
                }
                break;
            }
        }
    } else if (mouseX <= 5 * slot_side && mouseY >= resolution.y - slot_side - 20) {
        for (int i = 0; i < hudSlots.size(); i++) {
            if (hudSlots[i].x - slot_side / 2 <= mouseX && mouseX <= hudSlots[i].x + slot_side / 2 &&
                hudSlots[i].y - slot_side / 2 <= mouseY && mouseY <= hudSlots[i].y + slot_side / 2) {
                if (i == 0 && points.size() >= 1) {
                    points.pop_back();
                    selectedDefender = RED;
                } else if (i == 1 && points.size() >= 2) {
                    points.pop_back();
                    points.pop_back();
                    selectedDefender = BLUE;
                } else if (i == 2 && points.size() >= 2) {
                    points.pop_back();
                    points.pop_back();
                    selectedDefender = YELLOW;
                } else if (i == 3 && points.size() >= 3) {
                    points.pop_back();
                    points.pop_back();
                    points.pop_back();
                    selectedDefender = PURPLE;
                }
                std::cout << "Defender selected: " << selectedDefender << std::endl;
                break;
            }
        }
    }
}

void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}

void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Tema1::OnWindowResize(int width, int height) {}

float Tema1::GetDistance(float x1, float y1, float x2, float y2) {
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}
