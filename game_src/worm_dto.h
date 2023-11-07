#ifndef WORM_DTO_H
#define WORM_DTO_H


#include "position.h"

// should it be locked? 

class WormDTO {

private: 
    int id;
    int team;
    int health;
    Position position;

public:
    WormDTO(int id, int team, int health, Position position);
    int getId();
    int getTeam();
    int getHealth();
    Position getPosition();
    ~WormDTO();
};
#endif
