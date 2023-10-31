#ifndef GAME_LOBBY_H
#define GAME_LOBBY_H

#include "game.h"

#include <iostream>
#include <vector>

class GameLobby : public Game {

private: 
    std::vector<std::string> mapNames;
    int team;

public:
    GameLobby(std::vector<std::string> mapNames, int team);
    ~GameLobby();
    std::vector<std::string>& getMapNames() override;
    int getTeam() override;
    GameLobby& operator=(const GameLobby& other);

    GameLobby(const GameLobby& other);

};
#endif
