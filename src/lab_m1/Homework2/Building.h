//
// Created by alini on 12/16/2023.
//

#ifndef GFXFRAMEWORK_BUILDING_H
#define GFXFRAMEWORK_BUILDING_H

#include "WOTGameObject.h"

class Building : public WOTGameObject {
public:
    float getHx();

    void setHx(float hx);

    float getHy();

    void setHy(float hy);

    float getHz();

    void setHz(float hz);

    bool collision(glm::vec3 point) override;

protected:
    float hx, hy, hz;
};


#endif //GFXFRAMEWORK_BUILDING_H
