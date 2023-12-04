#include "game_map.h"

#include <iostream>

GameMap::GameMap(int team, int numberTeams, std::string mapName, std::vector<BeamDTO> beamsMap, std::unordered_map<int, WormDTO> worms) : 
Serializable(), 
team(team),
numberTeams(numberTeams),
mapName(mapName),
beamsMap(beamsMap),
worms(worms) {}

int GameMap::getTeam() {
    return this->team;
}

void GameMap::setTeam(int newTeam) {
    this->team = newTeam;
}

int GameMap::getNumberTeams() {
    return this->numberTeams;
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
std::unordered_map<int, WormDTO>GameMap::getWorms() {
    return this->worms;
}

void GameMap::send(Protocol& protocol) {
    protocol.sendSerializable(this);
}

int GameMap::getSerType() {
    return serializableType;
}

GameMap::~GameMap() {}