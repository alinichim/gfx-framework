#include <iostream>
#include "lab_m1/Homework1/Homework1.h"

#include "BoardBase.h"

#include "lab_m1/Homework1/Homework1object2D.h"
#include "lab_m1/Homework1/Homework1transform2D.h"

using namespace std;
using namespace m1;

Homework1::~Homework1() = default;

void Homework1::Init() {
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
    boardBase.setX(boardBase.getWidth() / 2 + BOARDBASE_LEFT_PADDING);
    boardBase.setY(boardBase.getHeight() / 2 + FOOTER_PADDING);
    boardBase.setZ(ZLEVEL_1);
    boardBase.setColor(glm::vec3(1, 0, 0));  // red color
    boardBase.setName("boardBase");
    AddMeshToList(boardBase.getMesh());

    // Add board slots to meshes
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            BoardSlot newSlot(GAMESLOT_SIDE);
            newSlot.setCenter(center);
            newSlot.setZ(ZLEVEL_1);
            newSlot.setX(GAMESLOT_SIDE / 2 + BOARDBASE_LEFT_PADDING + boardBase.getWidth() + SLOT_PADDING);
            newSlot.setY(GAMESLOT_SIDE / 2 + FOOTER_PADDING);
            float translateX = (float) j * (GAMESLOT_SIDE + SLOT_PADDING);
            float translateY = (float) i * (GAMESLOT_SIDE + SLOT_PADDING);
            newSlot.setX(newSlot.getX() + translateX);
            newSlot.setY(newSlot.getY() + translateY);
            newSlot.setColor(glm::vec3(0, 0.2, 0));  // green color
            newSlot.setName("boardSlot");
            boardSlots.push_back(newSlot);
        }
    }
    AddMeshToList(boardSlots[0].getMesh());

    // Add HUD slots to meshes
    HUDSlot newSlot(GAMESLOT_SIDE, 1);
    newSlot.setCenter(center);
    newSlot.setName("hudSlot");
    newSlot.setZ(ZLEVEL_1);
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
    gamePoint.setZ(ZLEVEL_1);
    gamePoint.setColor(glm::vec3(0.15f, 0.15f, 0.15f));  // grey color
    gamePoint.setName("defenderPrice");
    AddMeshToList(gamePoint.getMesh());
    // Add defender examples
    Defender newDefenderExample;
    newDefenderExample.setCenter(center);
    newDefenderExample.setZ(ZLEVEL_2);
    newDefenderExample.setLength(0.4f * GAMESLOT_SIDE);
    newDefenderExample.setColor(glm::vec3(1, 0, 0));  // red color
    newDefenderExample.setName("defenderExampleRed");
    defenderExamples.push_back(newDefenderExample);
    AddMeshToList(defenderExamples[0].getMesh());
    newDefenderExample.setColor(glm::vec3(0, 0, 1));  // blue color
    newDefenderExample.setName("defenderExampleBlue");
    defenderExamples.push_back(newDefenderExample);
    AddMeshToList(defenderExamples[1].getMesh());
    newDefenderExample.setColor(glm::vec3(1, 1, 0));  // yellow color
    newDefenderExample.setName("defenderExampleYellow");
    defenderExamples.push_back(newDefenderExample);
    AddMeshToList(defenderExamples[2].getMesh());
    newDefenderExample.setColor(glm::vec3(1, 0, 1));  // purple color
    newDefenderExample.setName("defenderExamplePurple");
    defenderExamples.push_back(newDefenderExample);
    AddMeshToList(defenderExamples[3].getMesh());

    // Add HUD health bar to meshes
    hudHealthBar.setHp(3);
    hudHealthBar.setSide(GAMESLOT_SIDE);
    hudHealthBar.setPoints(2);
    hudHealthBar.setCenter(center);
    hudHealthBar.setZ(ZLEVEL_1);
    hudHealthBar.setColor(glm::vec3(1, 0, 0));  // red color
    hudHealthBar.setName("healthBar");
    hudHealthBar.setPadding(SLOT_PADDING);
    AddMeshToList(hudHealthBar.getMesh());

    // Add collectable game point
    collectablePoint.setRadius(GAMEPOINT_RADIUS * 2);
    collectablePoint.setCenter(center);
    collectablePoint.setZ(ZLEVEL_3);
    collectablePoint.setColor(glm::vec3(0.8f, 0.0f, 0.7f));
    collectablePoint.setName("collectablePoint");
    AddMeshToList(collectablePoint.getMesh());
}

void Homework1::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0.2f, 0.2f, 0.2f, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

void Homework1::Update(float deltaTimeSeconds) {

    if (hudHealthBar.getHp() == 0) {
        window->Close();
        exit(0);
    }

    RenderObjects();

    // Add new points on screen
    pointsDeltaInterval += deltaTimeSeconds;
    if (pointsDeltaInterval >= pointsInterval) {
        pointsDeltaInterval -= pointsInterval;
        for (int i = 0; i < numberOfPoints; i++) {
            GamePoint newGamePoint = collectablePoint;
            std::random_device rd;
            std::mt19937 gen(rd());
            std::uniform_real_distribution<float> disX(0, (float) window->GetResolution().x);
            std::uniform_real_distribution<float> disY(0, (float) window->GetResolution().y);
            newGamePoint.setX(disX(gen));
            newGamePoint.setY(disY(gen));
            collectableGamePoints.push_back(newGamePoint);
        }
    }

    // Add new attackers
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<float> dis(ATTACKER_FR_MIN, ATTACKER_FR_MAX);
    attackerDeltaInterval += deltaTimeSeconds;
    float d = dis(gen);
    if (attackerDeltaInterval >= d) {
        attackerDeltaInterval -= d;
        Attacker newAttacker;
        newAttacker.setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
        newAttacker.setZ(ZLEVEL_2);
        newAttacker.setX((float) window->GetResolution().x);
        std::uniform_int_distribution<int> disLane(0, 2);
        newAttacker.setY(boardSlots[disLane(gen) * 3].getY());
        newAttacker.setRadius(0.2f * GAMESLOT_SIDE);
        std::uniform_int_distribution<int> disColor(0, 3);
        newAttacker.setColor(defenderExamples[disColor(gen)].getColor());
        newAttacker.setSpeed(ATTACKER_SPEED);
        if (newAttacker.getColor() == glm::vec3(0, 0, 1)) {
            newAttacker.setName("attackerBlue");
        } else if (newAttacker.getColor() == glm::vec3(1, 1, 0)) {
            newAttacker.setName("attackerYellow");
        } else if (newAttacker.getColor() == glm::vec3(1, 0, 1)) {
            newAttacker.setName("attackerPurple");
        } else {
            newAttacker.setName("attackerRed");
        }
        attackers.push_back(newAttacker);
        AddMeshToList(attackers[attackers.size() - 1].getMesh());
    }

    // Remove attackers
    for (int i = 0; i < attackers.size(); i++) {
        if (attackers[i].getX() <= boardBase.getX()) {
            hudHealthBar.setHp(hudHealthBar.getHp() - 1);
            meshes[hudHealthBar.getName()] = hudHealthBar.getMesh();
            attackers.erase(attackers.begin() + i);
        }
    }

    // Move attackers
    for (auto &attacker: attackers) {
        attacker.setX(attacker.getX() - attacker.getSpeed() * deltaTimeSeconds);
    }

    // Move projectiles
    for (auto &projectile: projectiles) {
        projectile.setX(projectile.getX() + projectile.getSpeed() * deltaTimeSeconds);
        projectile.setAngle(projectile.getAngle() - projectile.getSpeed() * deltaTimeSeconds);
    }

    // Check dead Active components
    for (int i = 0; i < attackers.size(); i++) {
        if (attackers[i].getHp() == 0) {
            if (attackers[i].getScale() <= 0.05f) {
                attackers.erase(attackers.begin() + i);
            } else {
                attackers[i].setScale(attackers[i].getScale() - 10.0f * deltaTimeSeconds);
            }
        }
    }
    for (int i = 0; i < projectiles.size(); i++) {
        if (projectiles[i].getHp() == 0) {
            projectiles.erase(projectiles.begin() + i);
        }
    }
    for (int i = 0; i < defenders.size(); i++) {
        if (defenders[i].getHp() == 0) {
            if (defenders[i].getScale() <= 0.05f) {
                defenders.erase(defenders.begin() + i);
            } else {
                defenders[i].setScale(defenders[i].getScale() - 10.0f * deltaTimeSeconds);
            }
        }
    }

    // Attacker detection
    for (auto &defender: defenders) {
        bool alreadyShot = false;
        for (auto &attacker: attackers) {
            if (glm::distance(glm::vec2(attacker.getX(), attacker.getY()),
                              glm::vec2(defender.getX(), defender.getY())) < GAMESLOT_SIDE / 2) {
                defender.setHp(0);
            }
            if (alreadyShot) {
                break;
            }
            if (defender.getHp() == 0) {
                continue;
            }
            if (attacker.getHp() == 0) {
                continue;
            }
            if (attacker.getColor() == defender.getColor() && attacker.getY() == defender.getY() &&
                attacker.getX() > defender.getX()) {
                defender.setDeltaTime(defender.getDeltaTime() + deltaTimeSeconds);
                if (defender.getDeltaTime() < defender.getFireRate()) {
                    break;
                }
                alreadyShot = true;
                defender.setDeltaTime(defender.getDeltaTime() - defender.getFireRate());
                // Shoot projectile
                Projectile newProjectile;
                newProjectile.setCenter(glm::vec3(0.0f, 0.0f, 0.0f));
                newProjectile.setZ(ZLEVEL_2);
                newProjectile.setX(defender.getX() + GAMESLOT_SIDE / 2);
                newProjectile.setY(attacker.getY());
                newProjectile.setRadius(0.2f * GAMESLOT_SIDE);
                newProjectile.setColor(attacker.getColor());
                newProjectile.setSpeed(PROJECTILE_SPEED);
                if (newProjectile.getColor() == glm::vec3(0, 0, 1)) {
                    newProjectile.setName("projectileBlue");
                } else if (newProjectile.getColor() == glm::vec3(1, 1, 0)) {
                    newProjectile.setName("projectileYellow");
                } else if (newProjectile.getColor() == glm::vec3(1, 0, 1)) {
                    newProjectile.setName("projectilePurple");
                } else {
                    newProjectile.setName("projectileRed");
                }
                projectiles.push_back(newProjectile);
                AddMeshToList(newProjectile.getMesh());
            }
        }
    }
    for (auto &projectile: projectiles) {
        if (projectile.getX() > window->GetResolution().x) {
            projectile.setHp(0);
            continue;
        }
        for (auto &attacker: attackers) {
            if (projectile.getY() != attacker.getY()) {
                continue;
            }
            if (projectile.getColor() != attacker.getColor()) {
                continue;
            }
            if (glm::distance(glm::vec2(projectile.getX(), projectile.getY()),
                              glm::vec2(attacker.getX(), attacker.getY())) <
                projectile.getRadius() + attacker.getRadius()) {
                attacker.setHp(max(0, attacker.getHp() - 1));
                projectile.setHp(0);
            }
        }
    }
}

void Homework1::FrameEnd() {}

/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */

void Homework1::OnInputUpdate(float deltaTime, int mods) {}

void Homework1::OnKeyPress(int key, int mods) {
    // Add key press event
}

void Homework1::OnKeyRelease(int key, int mods) {
    // Add key release event
}

void Homework1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event
    if (defenderSelected) {
        selectedDefender.setX(mouseX);
        selectedDefender.setY(window->GetResolution().y - mouseY);
    }
}

void Homework1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {

    if (button == GLFW_MOUSE_BUTTON_2) {
        LeftMouseButtonPressed(mouseX, mouseY);
    } else if (button == GLFW_MOUSE_BUTTON_3) {
        RightMouseButtonPressed(mouseX, mouseY);
    }
}

void Homework1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
    if (button == GLFW_MOUSE_BUTTON_2) {
        if (!defenderSelected) {
            return;
        }

        for (const auto &slot: boardSlots) {
            if (glm::distance(glm::vec2(mouseX, window->GetResolution().y - mouseY),
                              glm::vec2(slot.getX(), slot.getY())) < GAMESLOT_SIDE / 2) {
                for (auto &defender: defenders) {
                    if (defender.getX() == slot.getX() && defender.getY() == slot.getY()) {
                        defenderSelected = false;
                        return;
                    }
                }
                if (selectedDefender.getColor() == glm::vec3(1.0f, 0.0f, 0.0f)) {
                    if (hudHealthBar.getPoints() < 1) {
                        break;
                    }
                    hudHealthBar.setPoints(hudHealthBar.getPoints() - 1);
                } else if (selectedDefender.getColor() == glm::vec3(0.0f, 0.0f, 1.0f)) {
                    if (hudHealthBar.getPoints() < 2) {
                        break;
                    }
                    hudHealthBar.setPoints(hudHealthBar.getPoints() - 2);
                } else if (selectedDefender.getColor() == glm::vec3(1.0f, 1.0f, 0.0f)) {
                    if (hudHealthBar.getPoints() < 2) {
                        break;
                    }
                    hudHealthBar.setPoints(hudHealthBar.getPoints() - 2);
                } else {
                    if (hudHealthBar.getPoints() < 3) {
                        break;
                    }
                    hudHealthBar.setPoints(hudHealthBar.getPoints() - 3);
                }
                selectedDefender.setX(slot.getX());
                selectedDefender.setY(slot.getY());
                defenders.push_back(selectedDefender);
                break;
            }
        }
    }
    defenderSelected = false;
}

void Homework1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {}

void Homework1::OnWindowResize(int width, int height) {}

void Homework1::RenderObjects() {

    // Viewport
    glm::ivec2 resolution = window->GetResolution();

    glm::mat3 modelMatrix(1);
    float translateX = 0.0f;
    float translateY = 0.0f;
    float scale = 0.0f;

    // Render board base
    modelMatrix *= Homework1transform2D::Translate(boardBase.getX(), boardBase.getY());
    RenderMesh2D(meshes[boardBase.getName()], shaders["VertexColor"], modelMatrix);

    // Render board slots
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            modelMatrix = Homework1transform2D::Translate(boardSlots[i * 3 + j].getX(), boardSlots[i * 3 + j].getY());
            RenderMesh2D(meshes[boardSlots[0].getName()], shaders["VertexColor"], modelMatrix);
        }
    }

    // Render HUD slots
    modelMatrix = glm::mat3(1);
    translateX = GAMESLOT_SIDE / 2 + BOARDBASE_LEFT_PADDING;
    translateY = (float) resolution.y - GAMESLOT_SIDE / 2 - FOOTER_PADDING;
    for (auto &slot: hudSlots) {
        slot.setX(translateX);
        slot.setY(translateY);
    }
    modelMatrix *= Homework1transform2D::Translate(translateX, translateY);
    for (int i = 0; i < 4; i++) {
        glm::mat3 tempModelMatrix = modelMatrix;
        translateX = (float) i * (GAMESLOT_SIDE + SLOT_PADDING);
        hudSlots[i].setX(hudSlots[i].getX() + translateX);
        tempModelMatrix *= Homework1transform2D::Translate(translateX, 0);
        RenderMesh2D(meshes[hudSlots[0].getName()], shaders["VertexColor"], tempModelMatrix);
    }
    // Render Defender prices
    for (int i = 0; i < 4; i++) {
        modelMatrix = Homework1transform2D::Translate(hudSlots[i].getX(), hudSlots[i].getY());
        translateX = -hudSlots[i].getSide() / 2 + gamePoint.getRadius();
        translateY = -hudSlots[i].getSide() / 2 - gamePoint.getRadius();
        modelMatrix *= Homework1transform2D::Translate(translateX, translateY);
        RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        if (i > 0) {
            modelMatrix *= Homework1transform2D::Translate(gamePoint.getRadius() * 2.0f, 0);
            RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        }
        if (i > 2) {
            modelMatrix *= Homework1transform2D::Translate(gamePoint.getRadius() * 2.0f, 0);
            RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        }
    }
    // Render Defender examples
    for (int i = 0; i < 4; i++) {
        modelMatrix = Homework1transform2D::Translate(hudSlots[i].getX(), hudSlots[i].getY());
        RenderMesh2D(meshes[defenderExamples[i].getName()], shaders["VertexColor"], modelMatrix);
    }

    // Render health bar
    translateX = hudSlots[3].getX() + GAMESLOT_SIDE + SLOT_PADDING;
    translateY = hudSlots[3].getY();
    hudHealthBar.setX(translateX);
    hudHealthBar.setY(translateY);
    modelMatrix = Homework1transform2D::Translate(translateX, translateY);
    RenderMesh2D(meshes[hudHealthBar.getName()], shaders["VertexColor"], modelMatrix);
    // Render collected points
    translateX = hudHealthBar.getX() - GAMESLOT_SIDE / 2 + gamePoint.getRadius();
    translateY = hudHealthBar.getY() - GAMESLOT_SIDE / 2 - gamePoint.getRadius();
    modelMatrix = Homework1transform2D::Translate(translateX, translateY);
    for (int i = 0; i < hudHealthBar.getPoints(); i++) {
        RenderMesh2D(meshes[gamePoint.getName()], shaders["VertexColor"], modelMatrix);
        modelMatrix *= Homework1transform2D::Translate(gamePoint.getRadius() * 2.0f, 0);
    }

    // Render collectable game points
    for (auto &point: collectableGamePoints) {
        modelMatrix = Homework1transform2D::Translate(point.getX(), point.getY());
        RenderMesh2D(meshes[collectablePoint.getName()], shaders["VertexColor"], modelMatrix);
    }

    // Render attackers
    for (auto &attacker: attackers) {
        modelMatrix = Homework1transform2D::Translate(attacker.getX(), attacker.getY());
        modelMatrix *= Homework1transform2D::Scale(attacker.getScale(), attacker.getScale());
        RenderMesh2D(meshes[attacker.getName()], shaders["VertexColor"], modelMatrix);
    }

    // Render Projectiles
    for (auto &projectile: projectiles) {
        modelMatrix = Homework1transform2D::Translate(projectile.getX(), projectile.getY());
        modelMatrix *= Homework1transform2D::Rotate(projectile.getAngle());
        RenderMesh2D(meshes[projectile.getName()], shaders["VertexColor"], modelMatrix);
    }

    // Render defenders
    for (auto &defender: defenders) {
        modelMatrix = Homework1transform2D::Translate(defender.getX(), defender.getY());
        modelMatrix *= Homework1transform2D::Scale(defender.getScale(), defender.getScale());
        RenderMesh2D(meshes[defender.getName()], shaders["VertexColor"], modelMatrix);
    }
    if (defenderSelected) {
        modelMatrix = Homework1transform2D::Translate(selectedDefender.getX(), selectedDefender.getY());
        RenderMesh2D(meshes[selectedDefender.getName()], shaders["VertexColor"], modelMatrix);
    }
}

void Homework1::LeftMouseButtonPressed(int mouseX, int mouseY) {

    // Check game points
    for (int i = 0; i < collectableGamePoints.size(); i++) {
        if (glm::distance(glm::vec2(mouseX, window->GetResolution().y - mouseY),
                          glm::vec2(collectableGamePoints[i].getX(), collectableGamePoints[i].getY())) <
            collectableGamePoints[i].getRadius()) {
            collectableGamePoints.erase(collectableGamePoints.begin() + i);
            hudHealthBar.setPoints(hudHealthBar.getPoints() + 1);
            meshes[hudHealthBar.getName()] = hudHealthBar.getMesh();
            return;
        }
    }

    if (defenderSelected) {
        selectedDefender.setX(mouseX);
        selectedDefender.setY(window->GetResolution().y - mouseY);
        return;
    }

    // Check defender selection
    for (int i = 0; i < 4; i++) {
        if (glm::distance(glm::vec2(mouseX, window->GetResolution().y - mouseY),
                          glm::vec2(hudSlots[i].getX(), hudSlots[i].getY())) < GAMESLOT_SIDE / 2) {
            defenderSelected = true;
            selectedDefender = defenderExamples[i];
            selectedDefender.setX(mouseX);
            selectedDefender.setY(window->GetResolution().y - mouseY);
            selectedDefender.setZ(ZLEVEL_2);
            selectedDefender.setHp(1);
            return;
        }
    }
}

void Homework1::RightMouseButtonPressed(int mouseX, int mouseY) {

    // Check defenders
    for (auto &defender: defenders) {
        if (glm::distance(glm::vec2(mouseX, window->GetResolution().y - mouseY),
                          glm::vec2(defender.getX(), defender.getY())) < GAMESLOT_SIDE / 2) {
            defender.setHp(0);
            return;
        }
    }
}

Homework1::Homework1() = default;
