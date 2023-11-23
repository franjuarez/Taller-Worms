#ifndef LOBBY_H
#define LOBBY_H

#include <vector>
#include <string>
#include <iostream>


#include "player.h"
#include "match_starter.h"

#include "../shared_src/thread.h"
#include "../game_src/map_loading/maps_loader.h"
#include "team.h"

#include <atomic>

struct MatchesStruct {
    MatchStarter* matchStarter;
    Queue<std::shared_ptr<InfoStruct>>* infoQueue;

    MatchesStruct(MatchStarter* matchStarter, Queue<std::shared_ptr<InfoStruct>>* infoQueue) : matchStarter(matchStarter), infoQueue(infoQueue) {}
    ~MatchesStruct() {}
};

class Lobby : public Thread {
private:
    const std::string& hostname;
    Socket skt;
    int numberOfPlayers;
    std::string mapName;
    std::list<Player*> players;
    Queue<std::shared_ptr<Command>> commandQueue;
    
    std::unordered_map<std::string, MatchesStruct*> matches;

    void reapDead();
    void killAll();

    std::vector<Team> createTeams(std::vector<WormDTO>& worms);

    std::vector<WormDTO> createWorms(std::vector<WormPosition> wormsPositions);

    bool* playing;
public:

    Lobby(const std::string& hostname, int numberOfPLayers, std::string mapName, bool* playing);

    ~Lobby();
    void run() override;
};
#endif
