#include "game_map.h"

#include <iostream>

GameMap::GameMap(int numberOfBeams, std::string mapName, std::vector<BeamDTO> beamsMap ) : 
Serializable(), 
numberOfBeams(numberOfBeams), 
mapName(mapName),
beamsMap(beamsMap) {}

void GameMap::addBeam(int id, BeamDTO beam) {
    beamsMap[id] = beam;
}

std::string GameMap::getMapName() {
    return this->mapName;
}

int GameMap::getNumberOfBeams() {
    return this->numberOfBeams;
}

std::vector<BeamDTO> GameMap::getBeams(int id) {
    return this->beamsMap;
}

void GameMap::send(Protocol& protocol) {
    // protocol.sendLobby(this);
}

GameMap::~GameMap() {}