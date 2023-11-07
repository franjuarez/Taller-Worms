#include "worm_dto.h"

#include <iostream>

WormDTO::WormDTO(int id, int team, int health, Position position) 
: id(id), team(team), health(health), position(position) {}

int WormDTO::getId() {
    return this->id;
}

int WormDTO::getTeam() {
    return this->team;
}

int WormDTO::getHealth() {
    return this->health;
}

Position WormDTO::getPosition() {
    return this->position;
}

WormDTO::~WormDTO() {}