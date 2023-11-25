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
    float velX;
    float velY;
    int onGround;
    Position position;
    std::vector<int> weapons;

public:
    WormDTO(int id, int dir, int team, int health, float velX, float velY, int onGround, Position position, std::vector<int> weapons);
    int getId();
    int getDir();
    int getTeam();
    int getHealth();
    int isAlive();
    int isOnGround();
    float getX();
    float getY();
    float getVelX();
    float getVelY();
    void setTeam(int team);
    void addHealth(int health);
    Position getPosition();
    std::vector<int> getWeapons();
    WormDTO& operator=(const WormDTO& worm);
    ~WormDTO();
};
#endif
