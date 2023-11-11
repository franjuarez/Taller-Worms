#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "player.h"
#include "../shared_src/thread.h"


class Lobby {

private:
    Socket& skt;
    int numberOfPlayers;
    std::string mapName;
    std::vector<Player*> players;
    Queue<Command*> commandQueue;
    void reapDead();
    void killAll();
// should it have the game thread queue?
public:
    Lobby(Socket& skt, int numberOfPlayers, std::string mapName);
    ~Lobby();
    void run();
};
#endif
