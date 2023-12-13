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
#include "Defender.h"
#include "Attacker.h"
#include "Projectile.h"


#define GAMESLOT_SIDE 80.0f
#define BOARDBASE_WIDTH 50.0f
#define BOARDBASE_LEFT_PADDING 50.0f
#define SLOT_PADDING 20.0f
#define FOOTER_PADDING 50.0f
#define GAMEPOINT_RADIUS 10.0f
#define HUD_LEFT_PADDING 100.0f

#define ZLEVEL_1 0.0f
#define ZLEVEL_2 10.0f
#define ZLEVEL_3 20.0f

#define ATTACKER_FR_MIN 8.0f
#define ATTACKER_FR_MAX 10.0f

#define ATTACKER_SPEED 60.0f
#define PROJECTILE_SPEED 90.0f

namespace m1 {

    class Homework1 : public gfxc::SimpleScene {
    public:
        Homework1();

        ~Homework1() override;

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

        void RenderObjects();

        void LeftMouseButtonPressed(int mouseX, int mouseY);

        void RightMouseButtonPressed(int mouseX, int mouseY);

    protected:
        std::vector<BoardSlot> boardSlots;
        std::vector<HUDSlot> hudSlots;
        std::vector<Defender> defenderExamples;
        std::vector<Defender> defenders;
        std::vector<Attacker> attackers;
        std::vector<Projectile> projectiles;
        std::vector<GamePoint> collectableGamePoints;
        BoardBase boardBase;
        HUDHealthBar hudHealthBar;
        GamePoint gamePoint;
        GamePoint collectablePoint;

        const float pointsInterval = 8.0f;
        float pointsDeltaInterval = 0.0f;
        const int numberOfPoints = 3;

        float attackerDeltaInterval = 0.0f;

        bool defenderSelected = false;
        Defender selectedDefender;
    };
} // namespace m1
