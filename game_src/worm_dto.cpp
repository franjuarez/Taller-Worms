#include "worm_dto.h"

#include <iostream>

WormDTO::WormDTO(int id, int dir, int team, int health, float velX, float velY, int onGround, Position position, std::vector<int> weapons) 
: id(id), dir(dir), team(team), health(health), velX(velX), velY(velY), onGround(onGround), position(position), weapons(weapons) {}

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

int WormDTO::isOnGround() {
    return this->onGround;
}

float WormDTO::getVelX() {
    return this->velX;
}

float WormDTO::getVelY() {
    return this->velY;
}

int WormDTO::isAlive() {
    return this->health > 0;
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

std::vector<int> WormDTO::getWeapons(){
    return this->weapons;
}

void WormDTO::setTeam(int newTeam) {
    this->team = newTeam;
}

void WormDTO::addHealth(int newHealth) {
    this->health += newHealth;
}


WormDTO& WormDTO::operator=(const WormDTO& other) {
    if (this != &other) { 
        id = other.id;
        dir = other.dir;
        team = other.team;
        health = other.health;
        position = other.position;
        weapons = other.weapons;
    }
  return *this;
}

WormDTO::~WormDTO() {}