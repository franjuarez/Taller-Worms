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
    std::vector<Player*> players;
    void reapDead();
    void killAll();
// should it have the game thread queue?
public:
    Lobby(Socket& skt);
    ~Lobby();
    void run();
};
#endif
