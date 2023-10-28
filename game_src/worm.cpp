#include "worm.h"

#include <iostream>

Worm::Worm(int id, int team, int health, Position& position) 
: id(id), team(team), health(health), position(position) {}

int Worm::getId() {
    return this->id;
}

int Worm::getTeam() {
    return this->team;
}

int Worm::getHealth() {
    return this->health;
}

Position Worm::getPosition() {
    return this->position;
}

Worm::~Worm() {}