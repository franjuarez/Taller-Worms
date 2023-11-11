#include "worm_dto.h"

#include <iostream>

WormDTO::WormDTO(int id, int dir, int team, int health, int alive, Position position, std::map<int, int> weapons) 
: id(id), dir(dir), team(team), health(health), alive(alive), position(position), weapons(weapons) {}

int WormDTO::getId() {
    return this->id;
}

int WormDTO::getDir() {
    return this->dir;
}

int WormDTO::getTeam() {
    return this->team;
}

int WormDTO::getHealth() {
    return this->health;
}

int WormDTO::isAlive() {
    return this->alive;
}

float WormDTO::getX() {
    return this->position.getX();
}

float WormDTO::getY() {
    return this->position.getY();
}

Position WormDTO::getPosition() {
    return this->position;
}

std::map<int, int> WormDTO::getWeapons(){
    return this->weapons;
}


WormDTO& WormDTO::operator=(const WormDTO& other) {
    if (this != &other) { // Check for self-assignment
        id = other.id;
        dir = other.dir;
        team = other.team;
        health = other.health;
        alive = other.alive;
        position = other.position;
    }
  return *this;
}

WormDTO::~WormDTO() {}