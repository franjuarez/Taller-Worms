#ifndef WEAPONS_DTO_H
#define WEAPONS_DTO_H

#include "position.h"
#include "constants_game.h"

class ExplosivesDTO {
private:
// add un ID aca y al Protocolo
    int proyectileType;
    int id;
    Position position;
    float velX;
    float velY;
public:
    ExplosivesDTO(int proyectileType, int id, Position position, float velX, float velY);
    ExplosivesDTO& operator=(const ExplosivesDTO& worm);
    int getType();
    int getID();
    float getX();
    float getY();
    Position getPosition();
    float getVelX();
    float getVelY();
    ~ExplosivesDTO();
};
#endif
