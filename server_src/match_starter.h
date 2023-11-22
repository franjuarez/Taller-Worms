#ifndef MATCH_STARTER_H_
#define MATCH_STARTER_H_

#include "../game_src/game_map.h"
#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "player.h"

#include <iostream>
#include <string>
#include <list>

class MatchStarter : public Thread {

private:
    Queue<std::string>& matchNamesQueue;
    Queue<std::shared_ptr<Player>>& playerInfoQueue;
    std::string matchName;
    int numberOfPlayers;
    std::list<std::shared_ptr<Player>> players;
    std::shared_ptr<GameMap> gameMap;

public:
    MatchStarter(Queue<std::string>& matchNamesQueue, Queue<std::shared_ptr<Player>>& playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap);
    void run() override;
    ~MatchStarter();
};
#endif

