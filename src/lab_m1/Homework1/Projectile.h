//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_PROJECTILE_H
#define GFXFRAMEWORK_PROJECTILE_H

#include "ActiveGameObject.h"

class Projectile : public ActiveGameObject {
public:
    Projectile();

    Mesh *getMesh() override;

    std::vector<glm::vec3> getOffsets();

    float getSpeed() const;

    void setSpeed(float speed);

    float getRadius() const;

    void setRadius(float radius);

private:
    float speed;
    float radius;
};


#endif //GFXFRAMEWORK_PROJECTILE_H
