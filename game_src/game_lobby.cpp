#include "game_lobby.h"
#include "../shared_src/protocol.h"

GameLobby::GameLobby(std::vector<std::string> mapNames, int team) 
: Serializable(), mapNames(mapNames), team(team) {}   
    


std::vector<std::string>& GameLobby::getMapNames() {
    return this->mapNames;
}

int GameLobby::getTeam() {
    return this->team;
}

void GameLobby::send(Protocol& protocol) {
    protocol.sendLobby(*this);
}

GameLobby& GameLobby::operator=(const GameLobby& other) {
    if (this == &other) {
        return *this;
    }
    this->mapNames = other.mapNames;
    this->team = other.team;
    return *this;
}

GameLobby::GameLobby(const GameLobby& other) : Serializable(), mapNames(other.mapNames), team(other.team) {}


GameLobby::~GameLobby(){}