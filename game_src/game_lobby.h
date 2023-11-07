#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H

#include "../shared_src/protocol.h"
#include "serializable.h"

#include <iostream>
#include <vector>

class Protocol;
// class Serializable;

class GameLobby : public Serializable {

private: 
    std::vector<std::string> mapNames;
    int team;

public:
    GameLobby(std::vector<std::string> mapNames, int team);
    ~GameLobby();
    std::vector<std::string>& getMapNames();
    int getTeam();
    GameLobby& operator=(const GameLobby& other);
    void send(Protocol& protocol);
    GameLobby(const GameLobby& other);

};
#endif
