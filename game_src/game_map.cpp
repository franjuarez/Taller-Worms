#include "game_map.h"

#include <iostream>

GameMap::GameMap(int numberOfBeams, std::string mapName) : 
Game(numberOfBeams, mapName), 
numberOfBeams(numberOfBeams), 
mapName(mapName) {}

void GameMap::addBeam(int id, Beam beam) {
    beamsMap[id] = beam;
}

std::string GameMap::getMapName() {
    return this->mapName;
}

int GameMap::getNumberOfBeams() {
    return this->numberOfBeams;
}

std::vector<Beam> GameMap::getBeams(int id) {
    return this->beamsMap;
}


GameMap::~GameMap() {}