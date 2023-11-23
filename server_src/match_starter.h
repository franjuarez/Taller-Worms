#ifndef MATCH_STARTER_H_
#define MATCH_STARTER_H_

#include "../game_src/commands/command.h"

#include "status_broadcaster.h"
#include "../game_src/game_map.h"
#include "../shared_src/thread.h"
#include "../shared_src/queue.h"
#include "../shared_src/socket.h"
#include "player.h"
#include "team.h"

#include <utility>
#include <iostream>
#include <string>
#include <vector>
#include <list>

struct InfoStruct {
    Socket skt;

    // lo puedo usar para recibir los primeros mensajes .... 
    // y para enviar los nombres de los Matches y de los Maps
    InfoStruct(Socket&& socket) : skt(std::move(socket)) {}
    ~InfoStruct() {}

};


class MatchStarter : public Thread {

private:
    std::vector<Team> teams;
    Queue<std::shared_ptr<InfoStruct>>* playerInfoQueue;
    std::string matchName;
    int numberOfPlayers;
    std::list<Player*> players;
    std::shared_ptr<GameMap> gameMap;
    bool* playing;

    void killAll();

public:
    MatchStarter(std::vector<Team> teams, Queue<std::shared_ptr<InfoStruct>>* playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing);
    void run() override;
    ~MatchStarter();
};
#endif
