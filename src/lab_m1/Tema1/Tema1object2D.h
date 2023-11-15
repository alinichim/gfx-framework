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
                    glm::vec3 borderColor, glm::vec3 defenderColor);
Mesh *CreateHUDHealthBar(const std::string &name, glm::vec3 center, float width,
                         float height, glm::vec3 healthpointColor);

/**
 * Attacker's move animation
 */
glm::mat4 AttackerMoveAnimation(float delta);
} // namespace Tema1object2D
