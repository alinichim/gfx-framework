//
// Created by alinichim on 12/13/2023.
//
#include "lab_m1/Homework2/Homework2.h"

#include <vector>
#include <string>
#include <iostream>

using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */

Homework2::Homework2() = default;

Homework2::~Homework2()
= default;


void Homework2::Init()
{
//    {
//        Mesh* mesh = new Mesh("box");
//        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "primitives"), "box.obj");
//        meshes[mesh->GetMeshID()] = mesh;
//    }

    {
        Mesh *mesh = new Mesh("tank_hull");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_hull.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_track_left");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_track_left.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_track_right");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_track_right.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_wheels_left");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_wheels_left.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_wheels_right");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_wheels_right.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_turret");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_turret.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_gun");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_gun.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    {
        Mesh *mesh = new Mesh("tank_shell");
        mesh->LoadMesh(PATH_JOIN(window->props.selfDir, RESOURCE_PATH::MODELS, "tank"), "tank_shell.obj");
        meshes[mesh->GetMeshID()] = mesh;
    }

    // Create a shader program for drawing face polygon with the color of the normal
    {
        auto *shader = new Shader("HomeworkShader");
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Homework2", "shaders", "VertexShader.glsl"), GL_VERTEX_SHADER);
        shader->AddShader(PATH_JOIN(window->props.selfDir, SOURCE_PATH::M1, "Homework2", "shaders", "FragmentShader.glsl"), GL_FRAGMENT_SHADER);
        shader->CreateAndLink();
        shaders[shader->GetName()] = shader;
    }

    camera = new implemented::Camera();
    camera->Set(glm::vec3(0, 4, -10), glm::vec3(0, 3, 0), glm::vec3(0, 1, 0));
    camera->distanceToTarget = glm::distance(camera->position, glm::vec3(0, 3, 0));

    projectionMatrix = glm::perspective(RADIANS(fov), window->props.aspectRatio, z_near, z_far);
}


void Homework2::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}

float clamp_rotation(float x, float min=-M_PI / 4, float max=M_PI / 10) {
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    }
    return x;
}

void Homework2::Render_Player_Tank() {
    {
        // Body
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, player_tank.getPosition());
        modelMatrix = glm::rotate(modelMatrix, player_tank.getBodyRotationY(), glm::vec3(0, 1, 0));
        glm::vec3 color(0.0f);
        color.g = 0.15f;
        RenderSimpleMesh(meshes["tank_hull"], shaders["HomeworkShader"], modelMatrix, color);
        color.g = 0.1f;
        RenderSimpleMesh(meshes["tank_track_left"], shaders["HomeworkShader"], modelMatrix, color);
        color.g = 0.1f;
        RenderSimpleMesh(meshes["tank_track_right"], shaders["HomeworkShader"], modelMatrix, color);
        color.g = 0.05f;
        RenderSimpleMesh(meshes["tank_wheels_left"], shaders["HomeworkShader"], modelMatrix, color);
        RenderSimpleMesh(meshes["tank_wheels_right"], shaders["HomeworkShader"], modelMatrix, color);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, player_tank.getPosition());
        modelMatrix = glm::rotate(modelMatrix, player_tank.getTurretRotationY(), glm::vec3(0, 1, 0));
        glm::vec3 color(0.0f);
        color.g = 0.1f;
        RenderSimpleMesh(meshes["tank_turret"], shaders["HomeworkShader"], modelMatrix, color);
    }

    {
        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, player_tank.getPosition());
        modelMatrix = glm::rotate(modelMatrix, player_tank.getTurretRotationY(), glm::vec3(0, 1, 0));
        modelMatrix = glm::translate(modelMatrix, player_tank.getGunCenter());
        modelMatrix = glm::rotate(modelMatrix, clamp_rotation(player_tank.getGunRotationX()), glm::vec3(1, 0, 0));
        modelMatrix = glm::translate(modelMatrix, -player_tank.getGunCenter());
        glm::vec3 color(1.0f);
        color.g = 0.05f;
        RenderSimpleMesh(meshes["tank_gun"], shaders["HomeworkShader"], modelMatrix, color);
    }
}

void Homework2::Update(float deltaTimeSeconds)
{
//    {
//        glm::mat4 modelMatrix = glm::mat4(1);
//        modelMatrix = glm::translate(modelMatrix, glm::vec3(0, 1, 0));
//        // TODO(student): Add or change the object colors
//        RenderSimpleMesh(meshes["sphere"], shaders["LabShader"], modelMatrix);
//    }

    Render_Player_Tank();

    // filter shells
    auto removeCondition = [](TankShell shell){
        return shell.getPosition().y <= 0;
    };
    auto newEnd = std::remove_if(shells.begin(), shells.end(), removeCondition);
    shells.erase(newEnd, shells.end());

    // Render shells
    for (auto &shell : shells) {
        // move
        glm::vec3 position = shell.getPosition();
        glm::vec3 speed = shell.getSpeed();
        speed -= glm::vec3(0, 0.6f, 0) * deltaTimeSeconds;
        shell.setSpeed(speed);
        position += speed * deltaTimeSeconds;
        shell.setPosition(position);

        glm::mat4 modelMatrix = glm::mat4(1.0f);
        modelMatrix = glm::translate(modelMatrix, shell.getPosition());
        modelMatrix = glm::rotate(modelMatrix, shell.getRotationY(), glm::vec3(0, 1, 0));
        modelMatrix = glm::rotate(modelMatrix, clamp_rotation(shell.getRotationX()), glm::vec3(1, 0, 0));
        modelMatrix = glm::scale(modelMatrix, glm::vec3(0.1f));
        glm::vec3 color(1.0f);
        color.b = 0.05f;
        RenderSimpleMesh(meshes["tank_shell"], shaders["HomeworkShader"], modelMatrix, color);
    }
}


void Homework2::FrameEnd()
{
    DrawCoordinateSystem(camera->GetViewMatrix(), projectionMatrix);
}


void Homework2::RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 & modelMatrix, const glm::vec3 &color)
{
    if (!mesh || !shader || !shader->GetProgramID())
        return;

    // Render an object using the specified shader and the specified position
    glUseProgram(shader->program);

    GLint location = 0;

    // Set eye position (camera position) uniform
    glm::vec3 eyePosition = camera->GetTargetPosition();
    location = glGetUniformLocation(shader->program, "eye_position");
    glUniform3f(location, eyePosition.x, eyePosition.y, eyePosition.z);


    // TODO: extra channels

    location = glGetUniformLocation(shader->program, "frag_color");
    glUniform3f(location, color.r, color.g, color.b);


    // Bind model matrix
    location = glGetUniformLocation(shader->program, "Model");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(modelMatrix));

    // Bind view matrix
    glm::mat4 viewMatrix = camera->GetViewMatrix();
    location = glGetUniformLocation(shader->program, "View");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(viewMatrix));

    // Bind projection matrix
    location = glGetUniformLocation(shader->program, "Projection");
    glUniformMatrix4fv(location, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

    // Draw the object
    glBindVertexArray(mesh->GetBuffers()->m_VAO);
    glDrawElements(mesh->GetDrawMode(), static_cast<int>(mesh->indices.size()), GL_UNSIGNED_INT, nullptr);
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Homework2::OnInputUpdate(float deltaTime, int mods)
{
    // Add on input update event

    float cameraSpeed = 2.0f;
    // move the camera only if MOUSE_RIGHT button is pressed
    if (window->KeyHold(GLFW_KEY_W)) {
        camera->MoveForward(player_tank.getSpeed() * deltaTime, player_tank.getForward());
        player_tank.Move(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_A)) {
        player_tank.Steer(deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_S)) {
        camera->MoveForward(player_tank.getSpeed() * -deltaTime, player_tank.getForward());
        player_tank.Move(-deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_D)) {
        player_tank.Steer(-deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_Q)) {
        camera->TranslateUpward(-cameraSpeed * deltaTime);
    }

    if (window->KeyHold(GLFW_KEY_E)) {
        camera->TranslateUpward(cameraSpeed * deltaTime);
    }
}


void Homework2::OnKeyPress(int key, int mods)
{
    // Add on key press event
}


void Homework2::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Homework2::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    float sensivityOX = 0.01f;
    float sensivityOY = 0.01f;
    camera->RotateThirdPerson_OX(-sensivityOX * deltaY);
    camera->RotateThirdPerson_OY(-sensivityOY * deltaX);
    player_tank.setTurretRotationY(player_tank.getTurretRotationY()+ -sensivityOY * deltaX);
    player_tank.setGunRotationX(player_tank.getGunRotationX()+ sensivityOX * deltaY);
}


void Homework2::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2) {
        TankShell newShell;
        float rotx = clamp_rotation(player_tank.getGunRotationX());
        float roty = player_tank.getTurretRotationY();
        glm::vec3 speedVector = glm::normalize(glm::vec3(sin(roty) * cos(rotx), -sin(rotx), cos(roty) * cos(rotx)));
        newShell.setRotationX(rotx);
        newShell.setRotationY(roty);
        glm::vec4 position = glm::vec4(player_tank.getGunCenter(), 1);
        glm::mat4 modelMatrix = glm::mat4(1);
        modelMatrix = glm::rotate(modelMatrix, roty, glm::vec3(0, 1, 0));
        position = modelMatrix * position;
        newShell.setPosition(player_tank.getPosition() + glm::vec3(position) + 5.0f * speedVector);
        float speed = 2;
        newShell.setSpeed(speedVector * speed);
        shells.push_back(newShell);
    }
}


void Homework2::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Homework2::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Homework2::OnWindowResize(int width, int height)
{
}
