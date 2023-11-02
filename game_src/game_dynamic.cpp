#include "game_dynamic.h"

GameDynamic::GameDynamic(int wormPlayingID, std::vector<Worm>worms) : Game(wormPlayingID, worms), 
wormPlayingID(wormPlayingID), worms(worms) {}

void GameDynamic::addWorms(std::vector<Worm> wormVec) {
    worms = wormVec;
}

void GameDynamic::setWormPlayingID(int id) {
    this->wormPlayingID = id;
}

std::vector<Worm> GameDynamic::getWorms() {
    return this->worms;
}

int GameDynamic::getNumberOfWorms() {
    return this->worms.size();
}

int GameDynamic::getWormPlayingID() {
    return this->wormPlayingID;
}

GameDynamic::~GameDynamic() {}