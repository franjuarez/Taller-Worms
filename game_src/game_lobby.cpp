#include "game_lobby.h"


GameLobby::GameLobby(std::vector<std::string> mapNames, int team) 
: Game(mapNames, team), mapNames(mapNames), team(team) {}   
    


std::vector<std::string>& GameLobby::getMapNames() {
    return this->mapNames;
}

int GameLobby::getTeam() {
    return this->team;
}

GameLobby& GameLobby::operator=(const GameLobby& other) {
    if (this == &other) {
        return *this;
    }
    this->mapNames = other.mapNames;
    this->team = other.team;
    return *this;
}

GameLobby::GameLobby(const GameLobby& other) : Game(other.mapNames, other.team), mapNames(other.mapNames), team(other.team) {}


GameLobby::~GameLobby(){}