#include "worm_dto.h"

#include <iostream>

WormDTO::WormDTO(int id, int team, int health, Position position) 
: id(id), team(team), health(health), position(position) {}

// WormDTO::WormDTO(const WormDTO& other) 
// : id(other.id), team(other.team), health(other.health), position(other.position) {}

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

WormDTO& WormDTO::operator=(const WormDTO& other) {
    if (this != &other) { // Check for self-assignment
        id = other.id;
        team = other.team;
        health = other.health;
        position = other.position;
    }
  return *this;
}

WormDTO::~WormDTO() {}