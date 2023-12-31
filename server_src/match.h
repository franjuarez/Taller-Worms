#ifndef MATCH_STARTER_H_
#define MATCH_STARTER_H_

#include "status_broadcaster.h"
#include "../game_src/game_map.h"
#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/socket.h"
#include "../shared_src/protocol.h"
#include "player.h"
#include "team.h"

#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <list>

class Player;


class Match : public Thread {

private:
    std::vector<Team> teams;
    std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> playerInfoQueue;
    std::string matchName;
    int numberOfPlayers;
    std::list<Player*> players;
    std::shared_ptr<GameMap> gameMap;
    bool* playing;
    int* status;

    void killAll();
    
public:
    Match(std::vector<Team> teams, std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing, int* status);
    void run() override;
    ~Match();
};
#endif
