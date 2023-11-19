//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_DEFENDER_H
#define GFXFRAMEWORK_DEFENDER_H

#include "ActiveGameObject.h"

class Defender : public ActiveGameObject {
public:
    Defender();

    Defender(float fireRate, float length, float deltaTime);

    Mesh *getMesh() override;

    float getFireRate() const;

    void setFireRate(float fireRate);

    float getLength() const;

    void setLength(float length);

    float getDeltaTime() const;

    void setDeltaTime(float deltaTime);

private:
    float fireRate;
    float length;
    float deltaTime;
};


#endif //GFXFRAMEWORK_DEFENDER_H
