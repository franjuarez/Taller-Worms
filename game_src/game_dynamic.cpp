#include "game_dynamic.h"

GameDynamic::GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::vector<ProjectileDTO> proyectiles)
: Serializable() ,wormPlayingID(wormPlayingID), worms(worms), proyectiles(proyectiles) {}

void GameDynamic::send(Protocol& protocol) {
    protocol.sendDynamic(this);
}

void GameDynamic::addWorms(std::vector<WormDTO> wormVec) {
    worms = wormVec;
}

std::vector<WormDTO> GameDynamic::getWorms() {
    return this->worms;
}

std::vector<ProjectileDTO> GameDynamic::getProjectiles() {
    return this->proyectiles;
}

int GameDynamic::getWormPlayingID() {
    return this->wormPlayingID;
}

GameDynamic& GameDynamic::operator=(const GameDynamic& other) {
    if (this == &other) {
        return *this;
    }
    this->wormPlayingID = other.wormPlayingID;
    this->worms = other.worms;
    return *this;
}

GameDynamic::GameDynamic(const GameDynamic& other) : 
Serializable(), 
wormPlayingID(other.wormPlayingID), 
worms(other.worms) {}


GameDynamic::~GameDynamic() {}