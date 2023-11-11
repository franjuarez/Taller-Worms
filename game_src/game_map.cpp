#include "game_map.h"

#include <iostream>

GameMap::GameMap(int team, std::string mapName, std::vector<BeamDTO> beamsMap, std::vector<WormDTO> worms) : 
Serializable(), 
team(team),
mapName(mapName),
beamsMap(beamsMap),
worms(worms) {}

int GameMap::getTeam() {
    return this->team;
}

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