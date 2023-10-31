#include "game_lobby.h"


GameLobby::GameLobby(std::vector<std::string> mapNames, int team) 
: Game(), mapNames(mapNames), team(team) {}

std::vector<std::string>& GameLobby::getMapNames() {
    std::cout << "GameLobby::getMapNames()\n";
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

GameLobby::GameLobby(const GameLobby& other) : Game(other), mapNames(other.mapNames), team(other.team) {}


GameLobby::~GameLobby(){}