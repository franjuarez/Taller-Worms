#include "match.h"
#include "game_loop.h"
#include <string>
#include "player.h"


Match::Match(std::vector<Team> teams, std::shared_ptr<Queue<std::shared_ptr<InfoStruct>>> playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing) : 
teams(teams), playerInfoQueue(playerInfoQueue), matchName(matchName), gameMap(gameMap), playing(playing) {
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
        std::cout << "Creo al player!\n";
        players.push_back(player);
        player->start();
        idPlayer++;
    }

    GameLoop gameLoop(commandQueue, statusBroadcaster, gameMap, teams, playing);

    gameLoop.run();

    commandQueue.close();

    killAll();
}

void Match::killAll() {
    std::cout << "Killing all players\n";
    for (auto& player : players ) {
        if (player->isAlive()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
    std::cout << "All players killed\n";
}

Match::~Match() {}
