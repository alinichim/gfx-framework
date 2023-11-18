//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_BOARDBASE_H
#define GFXFRAMEWORK_BOARDBASE_H

#include "PassiveGameObject.h"
#include "components/simple_scene.h"

class BoardBase : public PassiveGameObject {
public:
    Mesh *getMesh() override;

    float getWidth() const;

    void setWidth(float width);

    float getHeight() const;

    void setHeight(float height);

private:
    float width;
    float height;
};


#endif //GFXFRAMEWORK_BOARDBASE_H
