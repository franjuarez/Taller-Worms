#ifndef WORM_DTO_H
#define WORM_DTO_H


#include "position.h"
#include <map>
// should it be locked? 

class WormDTO {

private: 
    int id;
    int dir;
    int team;
    int health;
    Position position;
    // type of weapon and amount
    std::map<int, int> weapons;

public:
    WormDTO(int id, int dir, int team, int health, Position position);
    int getId();
    int getDir();
    int getTeam();
    int getHealth();
    float getX();
    float getY();
    Position getPosition();
    WormDTO& operator=(const WormDTO& worm);
    ~WormDTO();
};
#endif
