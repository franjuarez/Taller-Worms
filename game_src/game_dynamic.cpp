#include "game_dynamic.h"

GameDynamic::GameDynamic(int wormPlayingID, std::vector<WormDTO>worms, std::unordered_map<int, ExplosivesDTO> explosives)
: Serializable() ,wormPlayingID(wormPlayingID), worms(worms), explosives(explosives) {}

void GameDynamic::send(Protocol& protocol) {
    protocol.sendDynamic(this);
}

void GameDynamic::addWorms(std::vector<WormDTO> wormVec) {
    worms = wormVec;
}

std::vector<WormDTO> GameDynamic::getWorms() {
    return this->worms;
}

std::unordered_map<int, ExplosivesDTO> GameDynamic::getExplosives() {
    return this->explosives;
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
    this->explosives = other.explosives;
    return *this;
}

GameDynamic::GameDynamic(const GameDynamic& other) : 
Serializable(), 
wormPlayingID(other.wormPlayingID), 
worms(other.worms) {}


GameDynamic::~GameDynamic() {}