#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>

#include "player.h"
#include "../shared_src/thread.h"
#include "../game_src/map_loading/maps_loader.h"
#include "team.h"

#include <atomic>

class Lobby : public Thread {
private:
    const std::string& hostname;
    Socket skt;
    int numberOfPlayers;
    std::string mapName;
    std::list<Player*> players;
    Queue<Command*> commandQueue;
    void reapDead();
    void killAll();
// should it have the game thread queue?

    std::vector<Team> createTeams(std::vector<WormDTO>& worms);

    bool* playing;
public:

    Lobby(const std::string& hostname, int numberOfPLayers, std::string mapName, bool* playing);

    ~Lobby();
    void run() override;
};
#endif
