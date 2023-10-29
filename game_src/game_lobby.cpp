#include "game_lobby.h"


GameLobby::GameLobby(std::vector<std::string>& mapNames, int team) 
: mapNames(mapNames), team(team) {}

std::vector<std::string>& GameLobby::getMapNames() {
    return this->mapNames;
}

int GameLobby::getTeam() {
    return this->team;
}

GameLobby::~GameLobby(){}