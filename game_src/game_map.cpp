#include "game_map.h"

#include <iostream>

GameMap::GameMap(int numberOfBeams, std::string mapName) : numberOfBeams(numberOfBeams), mapName(mapName) {}

void GameMap::addBeam(int id, Beam* beam) {
    beamsMap[id] = beam;
}

Position GameMap::getBeamPosition1(int id) {
    return beamsMap[id]->getPosition1();
}

Position GameMap::getBeamPosition2(int id) {
    return beamsMap[id]->getPosition2();
}

std::string GameMap::getMapName() {
    return this->mapName;
}

int GameMap::getNumberOfBeams() {
    return this->numberOfBeams;
}

int GameMap::getBeamLength(int id) {
    return beamsMap[id]->getBeamLength();
}

GameMap::~GameMap() {}