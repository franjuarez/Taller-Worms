#include "match_starter.h"
#include "game_loop.h"
#include <string>


MatchStarter::MatchStarter(std::vector<Team> teams, Queue<std::shared_ptr<InfoStruct>>* playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing) : 
teams(teams), playerInfoQueue(playerInfoQueue), matchName(matchName), gameMap(gameMap), playing(playing) {
    numberOfPlayers = gameMap->getNumberTeams();
}


void MatchStarter::run() {
    int idPlayer = 0;
    Queue<std::shared_ptr<Command>> commandQueue;
    StatusBroadcaster statusBroadcaster;
    while (idPlayer != numberOfPlayers) {

        // bloqueo el while con un pop de la queue de InfoStruct
        std::shared_ptr<InfoStruct> infoStruct = playerInfoQueue->pop();

        // le seteo el team al GameMap y lo uso para crear el nuevo Player
        std::shared_ptr<GameMap> playerMap = std::make_shared<GameMap>(idPlayer, numberOfPlayers, gameMap->getMapName(), gameMap->getBeams(), gameMap->getWorms());
        Player* player = new Player(std::move(infoStruct->skt), commandQueue, playerMap);
        
        statusBroadcaster.addPlayer(idPlayer, player->getPlayerQueue());
        players.push_back(player);
        
        idPlayer++;
    }
    bool loopActive = true;

    GameLoop gameLoop(commandQueue, statusBroadcaster, gameMap, teams, &loopActive);
    gameLoop.start();

    while (*playing) {}

    loopActive = false;

    killAll();

    gameLoop.join();

}

void MatchStarter::killAll() {
    for (auto& player : players ) {
        if (player->isAlive()) {
            player->kill();
        }
        player->join();
        delete player;
    }
    players.clear();
}



MatchStarter::~MatchStarter() {}
