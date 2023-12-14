#pragma once

#include "components/simple_scene.h"
#include "components/transform.h"
#include "lab_m1/Homework2/lab_camera.h"

#include "lab_m1/Homework2/Tank.h"

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
        glm::mat4 projectionMatrix;
        implemented::Camera *camera;
        float turret_rot = 0;
        float gun_rot_y = 0;
        float gun_rot_x = 0;
        float tz = 0;

        Tank player_tank;

        void Render_Player_Tank();
    };
}   // namespace m1
