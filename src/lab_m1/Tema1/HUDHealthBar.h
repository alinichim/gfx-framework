//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_HUDHEALTHBAR_H
#define GFXFRAMEWORK_HUDHEALTHBAR_H

#include "PassiveGameObject.h"

class HUDHealthBar : public PassiveGameObject {
public:
    HUDHealthBar(int hp, int points, const glm::vec3 pointsColor, float side, float padding);

    Mesh *getMesh() override;

    int getHp() const;

    void setHp(int hp);

    int getPoints() const;

    void setPoints(int points);

    const glm::vec3 &getPointsColor() const;

    void setPointsColor(const glm::vec3 &pointsColor);

    float getSide() const;

    void setSide(float side);

    float getPadding() const;

    void setPadding(float padding);

private:
    int hp;
    int points;
    glm::vec3 pointsColor;
    float side;
    float padding;
};


#endif //GFXFRAMEWORK_HUDHEALTHBAR_H
