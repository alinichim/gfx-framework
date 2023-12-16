//
// Created by alini on 12/14/2023.
//

#include "Tank.h"

#include <cmath>

float Tank::getGunRotationX() const {
    return gun_rotation_x;
}

void Tank::setGunRotationX(float gunRotationX) {
    gun_rotation_x = gunRotationX;
}

float Tank::getGunRotationY() const {
    return gun_rotation_y;
}

void Tank::setGunRotationY(float gunRotationY) {
    gun_rotation_y = gunRotationY;
}

float Tank::getTurretRotationY() const {
    return turret_rotation_y;
}

void Tank::setTurretRotationY(float turretRotationY) {
    turret_rotation_y = turretRotationY;
}

const glm::vec3 &Tank::getGunCenter() const {
    return gun_center;
}

void Tank::setGunCenter(const glm::vec3 &gunCenter) {
    gun_center = gunCenter;
}

int Tank::getHp() const {
    return hp;
}

void Tank::setHp(int hp) {
    Tank::hp = hp;
}

Tank::Tank(const glm::vec3 &position, const glm::vec3 &forward, float collisionMargin) {}

Tank::Tank() : WOTGameObject() {

}

void Tank::Move(float distance) {
    glm::vec3 dir = glm::normalize(glm::vec3(forward.x, 0, forward.z));
    position += dir * distance * speed;
}

float Tank::getSpeed() const {
    return speed;
}

void Tank::setSpeed(float speed) {
    Tank::speed = speed;
}

void Tank::Steer(float angle) {
    body_rotation_y += angle;
    glm::vec4 newVector =
            glm::rotate(glm::mat4(1.0f), angle, glm::vec3(0, 1, 0)) *
            glm::vec4(forward, 1);
    forward = glm::normalize(glm::vec3(newVector));
}

float Tank::getBodyRotationY() const {
    return body_rotation_y;
}

void Tank::setBodyRotationY(float bodyRotationY) {
    body_rotation_y = bodyRotationY;
}

bool Tank::collision(glm::vec3 point) {
    glm::vec3 dx, dy, dz;
    dx = glm::vec3(1, 0, 0);
    dy = glm::vec3(0, 1, 0);
    dz = glm::vec3(0, 0, 1);

    glm::mat4 modelMatrix(1);
    modelMatrix = glm::rotate(modelMatrix, body_rotation_y, glm::vec3(0, 1, 0));
    dx = glm::vec3(modelMatrix * glm::vec4(dx, 1));
    dz = glm::vec3(modelMatrix * glm::vec4(dz, 1));

    glm::vec3 half(2, 2, 3);

    glm::vec3 d = point - position;

    return glm::abs(glm::dot(d, dx)) <= half.x &&
            glm::abs(glm::dot(d, dy)) <= half.y &&
            glm::abs(glm::dot(d, dz)) <= half.z;
}

glm::vec3 Tank::collisionCallback(Tank &tank) {
    glm::vec3 dif = tank.getPosition() - position;
    glm::vec3 P = glm::normalize(dif);
    P = (tank.getRadius() + radius - glm::distance(tank.getPosition(), position)) * P;
    tank.setPosition(tank.getPosition() + P * 0.5f);
    position += P * -0.5f;
    return P * -0.5f;
}

float Tank::getProjectileSpeed() {
    return projectileSpeed;
}

void Tank::setProjectileSpeed(float projectileSpeed) {
    Tank::projectileSpeed = projectileSpeed;
}

float Tank::getRadius() {
    return radius;
}

void Tank::setRadius(float radius) {
    Tank::radius = radius;
}

glm::vec3 Tank::collisionCallback(Building &building) {
    glm::vec3 v[] = {
            glm::vec3(1.8f, 0, 3),
            glm::vec3(-1.8f, 0, 3),
            glm::vec3(-1.8f, 0, -3),
            glm::vec3(1.8f, 0, -3),
    };

    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, body_rotation_y, glm::vec3(0, 1, 0));
    glm::vec3 bpos = building.getPosition();
    float hx = building.getHx();
    float hz = building.getHz();

    for (int i = 0; i < 4; ++i) {
        v[i] = glm::vec3(modelMatrix * glm::vec4(v[i], 1));
        float dx = abs(v[i].x - bpos.x);
        float dz = abs(v[i].z - bpos.z);
        if (dx <= hx && dz <= hz) {
            glm::vec3 dif = v[i] - bpos;
            glm::vec3 P = glm::normalize(dif);
            position += P * std::min(hx - dx, hz - dz);
            return P * std::min(hx - dx, hz - dz);
        }
    }
    return glm::vec3(0);
}

bool Tank::collision(Building building) {
    glm::vec3 v[] = {
            glm::vec3(2, 0, 3),
            glm::vec3(-2, 0, 3),
            glm::vec3(-2, 0, -3),
            glm::vec3(2, 0, -3),
    };

    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, body_rotation_y, glm::vec3(0, 1, 0));
    glm::vec3 bpos = building.getPosition();
    float hx = building.getHx();
    float hz = building.getHz();
    for (int i = 0; i < 4; ++i) {
        v[i] = glm::vec3(modelMatrix * glm::vec4(v[i], 1));
        if ((v[i].x - bpos.x >= -hx && v[i].x - bpos.x <= hx) && (v[i].z - bpos.z >= -hz && v[i].z - bpos.z <= hz)) {
            return true;
        }
    }
    return false;
}

bool Tank::shellCollisionCallback(TankShell shell) {
    glm::mat4 modelMatrix(1);
    modelMatrix = glm::translate(modelMatrix, -position);
    modelMatrix = glm::rotate(modelMatrix, -body_rotation_y, glm::vec3(0, 1, 0));
    glm::vec3 spos = glm::vec3(modelMatrix * glm::vec4(shell.getPosition(), 1));
    float hx = 1.8f;
    float hz = 3.2f;
    return spos.x >= -hx && spos.x <= hx && spos.z >= -hz && spos.z <= hz;
}

float clamp_rotation(float x, float min, float max) {
    if (x < min) {
        return min;
    } else if (x > max) {
        return max;
    }
    return x;
}

bool Tank::Shoot(TankShell &shell) {
    // check if reloaded
    auto now = std::chrono::high_resolution_clock::now();
    if (std::chrono::duration_cast<std::chrono::seconds>(now - lastShoot).count() < 1) {
        return false;
    }
    lastShoot = now;

    float rotx = clamp_rotation(gun_rotation_x);
    float roty = turret_rotation_y;
    glm::vec3 speedVector = glm::normalize(glm::vec3(sin(roty) * cos(rotx), -sin(rotx), cos(roty) * cos(rotx)));
    shell.setRotationX(rotx);
    shell.setRotationY(roty);
    glm::vec4 sposition = glm::vec4(gun_center, 1);
    glm::mat4 modelMatrix = glm::mat4(1);
    modelMatrix = glm::rotate(modelMatrix, roty, glm::vec3(0, 1, 0));
    sposition = modelMatrix * sposition;
    shell.setPosition(this->position + glm::vec3(sposition) + 5.0f * speedVector);
    shell.setSpeed(speedVector * projectileSpeed);

    return true;
}

float clamp(float x, float lowerlimit = 0.0f, float upperlimit = 1.0f) {
    if (x < lowerlimit) return lowerlimit;
    if (x > upperlimit) return upperlimit;
    return x;
}

float smoothstep(float x, float edge0, float edge1) {
    x = clamp((x - edge0) / (edge1 - edge0));

    return x * x * x * (x * (6.0f * x - 15.0f) + 10.0f);
}

void Tank::AimAt(glm::vec3 position) {
    glm::vec3 dif = glm::normalize(position - this->position);
    glm::vec3 forward(0, 0, 1);
    float angle = std::acos(glm::dot(forward, dif));
    turret_rotation_y = (dif.x >= 0) ? angle : M_PI * 2 - angle;
    float dist = glm::distance(position, this->position);
    gun_rotation_x = clamp_rotation(-smoothstep(dist, 8, 200));
}
