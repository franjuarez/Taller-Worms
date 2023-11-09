#ifndef PROJECTILE_DTO_H
#define PROJECTILE_DTO_H

#include "position.h"
#include "constants_game.h"

class ProjectileDTO {
private:
    int proyectileType;
    Position position;
    float velX;
    float velY;
public:
    ProjectileDTO(int proyectileType, Position position, float velX, float velY);
    int getType();
    float getX();
    float getY();
    Position getPosition();
    float getVelX();
    float getVelY();
    ~ProjectileDTO();
};
#endif