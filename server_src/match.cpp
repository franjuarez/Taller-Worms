#include "match.h"
#include "game_loop.h"
#include <string>
#include "player.h"
#include "../shared_src/info_struct.h"
#include "constants_server.h"


Match::Match(std::vector<Team> teams, std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap,
 bool* playing, int* status) : 
teams(teams), playerInfoQueue(playerInfoQueue), matchName(matchName), gameMap(gameMap), playing(playing), status(status) {
    numberOfPlayers = gameMap->getNumberTeams();
}


void Match::run() {
    int idPlayer = 0;
    Queue<std::shared_ptr<Command>> commandQueue(90);
    StatusBroadcaster statusBroadcaster;
    while (idPlayer != numberOfPlayers) {
        std::shared_ptr<InfoStruct> infoStruct = playerInfoQueue->pop();

        std::shared_ptr<GameMap> playerMap = std::make_shared<GameMap>(idPlayer, numberOfPlayers, gameMap->getMapName(), gameMap->getBeams(), gameMap->getWorms());
        Player* player = new Player(infoStruct, idPlayer, commandQueue, statusBroadcaster, playerMap);
        players.push_back(player);
        player->start();
        idPlayer++;
    }

    GameLoop gameLoop(commandQueue, statusBroadcaster, gameMap, teams, playing);

    *status = MATCH_IN_GAME_LOOP;

    gameLoop.run();


    commandQueue.close();

    killAll();

    *status = MATCH_OVER;
}


void Match::killAll() {
    for (auto& player : players ) {
        if (player->isAlive()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
}

Match::~Match() {}
