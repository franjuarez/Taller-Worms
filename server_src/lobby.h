#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "player.h"

class Lobby {

private:
    Socket& skt;
    std::vector<Player*> players;
// should it have the game thread queue?
public:
    Lobby(Socket& skt);
    ~Lobby();
    void start();
};
#endif