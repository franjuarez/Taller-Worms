#include "game_map.h"

#include <iostream>

GameMap::GameMap(std::string mapName, std::vector<BeamDTO> beamsMap, std::vector<WormDTO> worms) : 
Serializable(), 
mapName(mapName),
beamsMap(beamsMap),
worms(worms) {}

std::string GameMap::getMapName() {
    return this->mapName;
}

int GameMap::getNumberOfBeams() {
    return this->beamsMap.size();
}

int GameMap::getNumberOfWorms() {
    return this->worms.size();
}

std::vector<BeamDTO> GameMap::getBeams() {
    return this->beamsMap;
}
std::vector<WormDTO> GameMap::getWorms() {
    return this->worms;
}

void GameMap::send(Protocol& protocol) {
    protocol.sendMap(this);
}

GameMap::~GameMap() {}