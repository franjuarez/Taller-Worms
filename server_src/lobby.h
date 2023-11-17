#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "player.h"
#include "../shared_src/thread.h"
#include "team.h"

class Lobby {
private:
    const std::string& hostname;
    Socket skt;
    int numberOfPlayers;
    std::string mapName;
    std::vector<Player*> players;
    Queue<Command*> commandQueue;
    void reapDead();
    void killAll();
// should it have the game thread queue?

    std::vector<Team> createTeams(std::vector<WormDTO>& worms);
public:

    Lobby(const std::string& hostname, int numberOfPLayers, std::string mapName);

    ~Lobby();
    void run();
};
#endif
