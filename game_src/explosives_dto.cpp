#include "explosives_dto.h"

ExplosivesDTO::ExplosivesDTO(int proyectileType, int id, Position position, float velX, float velY) : 
proyectileType(proyectileType), id(id),
position(position), velX(velX), velY(velY) {}

int ExplosivesDTO::getType() {
    return this->proyectileType;
}

int ExplosivesDTO::getID() {
    return this->id;
}

float ExplosivesDTO::getX() {
    return this->position.getX();
}

float ExplosivesDTO::getY() {
    return this->position.getY();
}

Position ExplosivesDTO::getPosition() {
    return this->position;
}

float ExplosivesDTO::getVelX() {
    return this->velX;
}

float ExplosivesDTO::getVelY() {
    return this->velY;
}

ExplosivesDTO::~ExplosivesDTO() {}