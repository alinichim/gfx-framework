//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_GAMEPOINT_H
#define GFXFRAMEWORK_GAMEPOINT_H

#include "PassiveGameObject.h"

class GamePoint : public PassiveGameObject {
public:
    GamePoint();

    explicit GamePoint(float radius);

    std::vector<glm::vec3> getOffsets();

    Mesh *getMesh() override;

    float getRadius() const;

    void setRadius(float radius);

protected:
    float radius;
};


#endif //GFXFRAMEWORK_GAMEPOINT_H
