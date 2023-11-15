#ifndef POWER_UPS_DTO_H
#define POWER_UPS_DTO_H

#include "position.h"
#include "explosives_dto.h"

class PowerUps {
private:
    ExplosivesDTO content;
    Position pos;
public:
    PowerUps(ExplosivesDTO content, Position pos);
    float getX();
    float getY();
    ExplosivesDTO getContent();
    ~PowerUps();
};
#endif
