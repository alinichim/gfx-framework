#pragma once

#include "components/simple_scene.h"
#include <vector>
#include <random>
#include <utility>

#include "BoardSlot.h"
#include "HUDSlot.h"
#include "BoardBase.h"
#include "HUDHealthBar.h"
#include "GamePoint.h"


#define GAMESLOT_SIDE 80.0f
#define BOARDBASE_WIDTH 50.0f
#define BOARDBASE_LEFT_PADDING 50.0f
#define SLOT_PADDING 20.0f
#define FOOTER_PADDING 50.0f
#define GAMEPOINT_RADIUS 10.0f
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
        std::vector<BoardSlot> boardSlots;
        std::vector<HUDSlot> hudSlots;
        BoardBase boardBase;
        HUDHealthBar hudHealthBar;
        GamePoint gamePoint;
    };
} // namespace m1
