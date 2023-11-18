//
// Created by alinichim on 11/18/23.
//

#ifndef GFXFRAMEWORK_DEFENDER_H
#define GFXFRAMEWORK_DEFENDER_H

#include "ActiveGameObject.h"

class Defender : public ActiveGameObject {
public:
    Defender();

    Mesh *getMesh() override;

    float getFireRate() const;

    void setFireRate(float fireRate);

    float getLength() const;

    void setLength(float length);

private:
    float fireRate;
    float length;
};


#endif //GFXFRAMEWORK_DEFENDER_H
