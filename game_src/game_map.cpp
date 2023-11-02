#include "game_map.h"

#include <iostream>

GameMap::GameMap(int numberOfBeams, std::string mapName, std::vector<Beam> beamsMap ) : 
Game(numberOfBeams, mapName, beamsMap), 
numberOfBeams(numberOfBeams), 
mapName(mapName),
beamsMap(beamsMap) {}

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