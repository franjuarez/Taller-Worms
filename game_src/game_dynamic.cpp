#include "game_dynamic.h"

GameDynamic::GameDynamic(int wormPlayingID) : wormPlayingID(wormPlayingID) {}

void GameDynamic::addWorm(Worm* worm) {
    worms.push_back(worm);
}

void GameDynamic::setWormPlayingID(int id) {
    this->wormPlayingID = id;
}

std::vector<Worm*> GameDynamic::getWorms() {
    return this->worms;
}

int GameDynamic::getNumberOfWorms() {
    return this->worms.size();
}

int GameDynamic::getWormPlayingID() {
    return this->wormPlayingID;
}

GameDynamic::~GameDynamic() {}