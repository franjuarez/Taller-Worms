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

struct InfoStruct {
    Protocol prot;

    // lo puedo usar para recibir los primeros mensajes .... 
    // y para enviar los nombres de los Matches y de los Maps
    InfoStruct(Socket&& socket) : prot(std::move(socket)) {}
    ~InfoStruct() {}

};

class Match : public Thread {

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
    Match(std::vector<Team> teams, Queue<std::shared_ptr<InfoStruct>>* playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing);
    void run() override;
    ~Match();
};
#endif
