#ifndef WORM_DTO_H
#define WORM_DTO_H

#include "position.h"
#include <vector>

class WormDTO {

private: 
    int id;
    int dir;
    int team;
    int health;
    Position position;
    std::vector<int> weapons;

public:
    WormDTO(int id, int dir, int team, int health, Position position, std::vector<int> weapons);
    int getId();
    int getDir();
    int getTeam();
    int getHealth();
    int isAlive();
    float getX();
    float getY();
    void setTeam(int team);
    void addHealth(int health);
    Position getPosition();
    std::vector<int> getWeapons();
    WormDTO& operator=(const WormDTO& worm);
    ~WormDTO();
};
#endif
