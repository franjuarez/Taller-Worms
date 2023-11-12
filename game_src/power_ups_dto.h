#ifndef POWER_UPS_DTO_H
#define POWER_UPS_DTO_H

#include "position.h"
#include "weapons_dto.h"

class PowerUps {
private:
    WeaponDTO content;
    Position pos;
public:
    PowerUps(WeaponDTO content, Position pos);
    float getX();
    float getY();
    WeaponDTO getContent();
    ~PowerUps();
};
#endif
