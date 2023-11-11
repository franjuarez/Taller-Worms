#include "weapons_dto.h"

WeaponDTO::WeaponDTO(int proyectileType, int boomed, Position position, float velX, float velY) : 
proyectileType(proyectileType), boomed(boomed),
position(position), velX(velX), velY(velY) {}

int WeaponDTO::getType() {
    return this->proyectileType;
}

int WeaponDTO::getBoomed() {
    return this->boomed;
}

float WeaponDTO::getX() {
    return this->position.getX();
}

float WeaponDTO::getY() {
    return this->position.getY();
}

Position WeaponDTO::getPosition() {
    return this->position;
}

float WeaponDTO::getVelX() {
    return this->velX;
}

float WeaponDTO::getVelY() {
    return this->velY;
}

WeaponDTO::~WeaponDTO() {}