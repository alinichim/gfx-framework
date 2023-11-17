#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"

namespace Tema1object2D {

    Mesh *CreateSlot(const std::string &name, glm::vec3 center, float length,
                     glm::vec3 color);

    Mesh *CreateBase(const std::string &name, glm::vec3 center, float width,
                     float height, glm::vec3 color);

    Mesh *CreateDefender(const std::string &name, glm::vec3 center, float length,
                         glm::vec3 color);

    Mesh *CreateAttacker(const std::string &name, glm::vec3 center, float length,
                         glm::vec3 colorOuter, glm::vec3 colorInner);

    Mesh *CreateStar(const std::string &name, glm::vec3 center, float length,
                     glm::vec3 color);

    Mesh *CreateHUDSlot(const std::string &name, glm::vec3 center, float length,
                        glm::vec3 borderColor);

    /**
     * Attacker's move animation
     * @param delta
     * @return Animation's transform matrix
     */
    glm::mat3 AttackerMoveAnimation(float delta);

    /**
     * Projectile's move animation
     * @param delta
     * @return Animation's transform matrix
     */
    glm::mat3 ProjectileMoveAnimation(float delta, float deltaX, float deltaY);
} // namespace Tema1object2D
