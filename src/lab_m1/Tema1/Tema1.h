#pragma once

#include "components/simple_scene.h"
#include <vector>
#include <random>
#include <utility>

#define SLOT_SIDE 80.0f
#define BASE_WIDTH 50.0f
#define BASE_LEFT_PADDING 50.0f
#define SLOT_PADDING 20.0f
#define FOOTER_PADDING 50.0f
#define HUD_LEFT_PADDING 100.0f

namespace m1 {

    enum ColorType {
        NOCOL, RED, BLUE, YELLOW, PURPLE
    };

    typedef struct positionData {
        float angle;
        float x;
        float y;
        float scale;

        positionData() : angle(0), x(0), y(0), scale(1.0f) {};

        positionData(float angle, float x, float y) : angle(angle), x(x), y(y), scale(1.0f) {};
    } PositionData;

    typedef struct objectData {
        int hp;
        ColorType color;
        PositionData position;

        objectData() : hp(0), color(NOCOL), position(0, 0, 0) {};

        objectData(int hp, ColorType color, PositionData position) : hp(hp), color(color), position(position) {};
    } ObjectData;

    class Tema1 : public gfxc::SimpleScene {
    public:
        Tema1();

        ~Tema1() override;

        void Init() override;

        struct ViewportSpace {
            ViewportSpace() : x(0), y(0), width(1), height(1) {}

            ViewportSpace(int x, int y, int width, int height)
                    : x(x), y(y), width(width), height(height) {}

            int x;
            int y;
            int width;
            int height;
        };

        struct LogicSpace {
            LogicSpace() : x(0), y(0), width(1), height(1) {}

            LogicSpace(float x, float y, float width, float height)
                    : x(x), y(y), width(width), height(height) {}

            float x;
            float y;
            float width;
            float height;
        };

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

        void AddPoint();

        void ConsumePoints(int numberOfPoints);

        void ConsumeHealthPoint();

        float GetDistance(float x1, float y1, float x2, float y2);


    protected:
        glm::mat3 modelMatrix{};
        const float slot_side = SLOT_SIDE;
        const float base_height = SLOT_SIDE * 3 + SLOT_PADDING * 2;
        const float base_width = BASE_WIDTH;
        const float defender_length = SLOT_SIDE * 0.8f;
        const float attacker_length = SLOT_SIDE * 0.3f;
        const float star_length = SLOT_SIDE * 0.16f;
        const float base_left_padding = BASE_LEFT_PADDING;
        const float slot_padding = SLOT_PADDING;
        const float footer_padding = FOOTER_PADDING;
        const float hud_left_padding = HUD_LEFT_PADDING;


        std::vector<PositionData> slots;
        std::vector<PositionData> hudSlots;
        std::vector<ObjectData> defenders;
        std::vector<ObjectData> attackers;
        std::vector<ObjectData> projectiles;
        std::vector<PositionData> collectablePoints;
        std::vector<PositionData> points = {PositionData(0, 0, 0), PositionData(0, 0, 0)};
        std::vector<PositionData> healthPoints;
        PositionData base;

        ColorType selectedDefender = NOCOL;

        std::random_device rd;

        const float pointsDeltaTime = 5.0f;
        float pointsTimePassed = 0.0f;
        float attackerTime = 0.0f;
        const float defenderFireRate = 2.0f;

        LogicSpace logicSpace;

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear);

        glm::mat3 VisualizationTransf2D(const LogicSpace &logicSpace, const ViewportSpace &viewSpace);
    };
} // namespace m1
