#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "player.h"
#include "../shared_src/thread.h"


class Lobby {

private:
    const std::string& hostname;
    Socket skt;
    int AMOUNT_OF_PLAYERS;
    std::vector<Player*> players;
    Queue<Command*> commandQueue;
    void reapDead();
    void killAll();
// should it have the game thread queue?
public:
    //Lobby(Socket& skt, int AMOUNT_OF_PLAYERS);
    Lobby(const std::string& hostname, int AMOUNT_OF_PLAYERS);
    ~Lobby();
    void run();
};
#endif
