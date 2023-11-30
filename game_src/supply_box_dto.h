#ifndef POWER_UPS_DTO_H
#define POWER_UPS_DTO_H

#include "position.h"
#include "explosives_dto.h"

class SupplyBoxDTO {
private:
    int id;
    int content;
    int falling;
    Position pos;
public:
    SupplyBoxDTO(int id, int content, int falling, Position pos);
    float getX();
    float getY();
    int getContent();
    int getID();
    int isFalling();
    ~SupplyBoxDTO();
};
#endif
