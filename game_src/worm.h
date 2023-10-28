#ifndef WORM_H
#define WORM_H

#include "position.h"

// should it be locked? 

class Worm {

private: 
    int id;
    int team;
    int health;
    Position position;

public:
    Worm(int, int, int, Position&);
    int getId();
    int getTeam();
    int getHealth();
    Position getPosition();
    ~Worm();

};
#endif
