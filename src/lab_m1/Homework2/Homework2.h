#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Homework2/lab_camera.h"

#include "lab_m1/Homework2/Tank.h"
#include "TankShell.h"
#include "Building.h"

#include <random>

namespace m1
{
    class Homework2 : public gfxc::SimpleScene
    {
    public:
        Homework2();
        ~Homework2() override;

        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void RenderSimpleMesh(Mesh *mesh, Shader *shader, const glm::mat4 &modelMatrix, const glm::vec3 &color = glm::vec3(1));

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        // TODO(student): If you need any other class variables, define them here.

        float z_near = 0.01;
        float z_far = 200;
        float fov = 40;
        float left = 0;
        float right = 0;
        int tank_hp = 3;
        glm::mat4 projectionMatrix;
        implemented::Camera *camera;

        Tank player_tank;
        std::vector<Tank> enemy_tanks;
        std::vector<TankShell> shells;
        std::vector<Building> buildings;

        void Render_Tank(Tank tank);
    };
}   // namespace m1
