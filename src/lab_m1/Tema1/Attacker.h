//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_ATTACKER_H
#define GFXFRAMEWORK_ATTACKER_H

#include "ActiveGameObject.h"

class Attacker : public ActiveGameObject {
public:
    Attacker();

    Mesh *getMesh() override;

    float getSpeed() const;

    void setSpeed(float speed);

    float getRadius() const;

    void setRadius(float radius);

private:
    float speed;
    float radius;

};


#endif //GFXFRAMEWORK_ATTACKER_H
