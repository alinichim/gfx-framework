#pragma once

#include "components/simple_scene.h"
#include <vector>

#define SLOT_SIDE 80.0f
#define BASE_WIDTH 50.0f
#define BASE_LEFT_PADDING 50.0f
#define SLOT_PADDING 20.0f
#define FOOTER_PADDING 50.0f
#define HUD_LEFT_PADDING 100.0f

namespace m1 {

    class Tema1 : public gfxc::SimpleScene {
    public:
        Tema1();

        ~Tema1() override;

        void Init() override;

    private:
        void FrameStart() override;

        void Update(float deltaTimeSeconds) override;

        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;

        void OnKeyPress(int key, int mods) override;

        void OnKeyRelease(int key, int mods) override;

        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;

        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;

        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;

        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;

        void OnWindowResize(int width, int height) override;

    protected:
        glm::mat3 modelMatrix{};
        const float slot_side = SLOT_SIDE;
        const float base_height = SLOT_SIDE * 3 + SLOT_PADDING * 2;
        const float base_width = BASE_WIDTH;
        const float defender_length = SLOT_SIDE * 0.8f;
        const float attacker_length = SLOT_SIDE * 0.6f;
        const float star_length = SLOT_SIDE * 0.5f;
        const float base_left_padding = BASE_LEFT_PADDING;
        const float slot_padding = SLOT_PADDING;
        const float footer_padding = FOOTER_PADDING;
        const float hud_left_padding = HUD_LEFT_PADDING;

        std::vector<glm::mat3> slots;
        std::vector<glm::mat3> hudSlots;
        std::vector<glm::mat3> defenders;
        std::vector<glm::mat3> attackers;
        std::vector<glm::mat3> collectablePoints;
        std::vector<glm::mat3> healthPoints;
        glm::mat3 base{};
        int numberOfPoints;
    };
} // namespace m1
