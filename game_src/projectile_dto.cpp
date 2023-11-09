#include "projectile_dto.h"

ProjectileDTO::ProjectileDTO(int proyectileType, Position position, float velX, float velY) : 
proyectileType(proyectileType),
position(position), velX(velX), velY(velY) {}

int ProjectileDTO::getType() {
    return this->proyectileType;
}

float ProjectileDTO::getX() {
    return this->position.getX();
}

float ProjectileDTO::getY() {
    return this->position.getY();
}

Position ProjectileDTO::getPosition() {
    return this->position;
}

float ProjectileDTO::getVelX() {
    return this->velX;
}

float ProjectileDTO::getVelY() {
    return this->velY;
}

ProjectileDTO::~ProjectileDTO() {}