//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_BOARDBASE_H
#define GFXFRAMEWORK_BOARDBASE_H

#include "PassiveGameObject.h"

class BoardBase : public PassiveGameObject {
public:
    Mesh *getMesh() override;
};


#endif //GFXFRAMEWORK_BOARDBASE_H
