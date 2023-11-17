//
// Created by alinichim on 11/17/23.
//

#ifndef GFXFRAMEWORK_GAMEOBJECT_H
#define GFXFRAMEWORK_GAMEOBJECT_H

#include "components/simple_scene.h"
#include <string>

#define DEFAULT_GAMEOBJECT_NAME "NONAME"

class GameObject {
public:
    GameObject();

    GameObject(float scale, float angle, float x, float y, float z, std::string name, glm::vec3 center);

    ~GameObject();

    virtual Mesh *getMesh() = 0;

    float getScale() const;

    void setScale(float scale);

    float getAngle() const;

    void setAngle(float angle);

    float getX() const;

    void setX(float x);

    float getY() const;

    void setY(float y);

    float getZ() const;

    void setZ(float z);

    const std::string &getName() const;

    void setName(const std::string &name);

    const glm::vec3 &getCenter() const;

    void setCenter(const glm::vec3 &center);

protected:
    float scale;
    float angle;
    float x, y, z;
    std::string name;
    glm::vec3 center;
};


#endif //GFXFRAMEWORK_GAMEOBJECT_H
