#include "match.h"
#include "game_loop.h"
#include <string>
#include "player.h"


Match::Match(std::vector<Team> teams, Queue<std::shared_ptr<InfoStruct>>* playerInfoQueue, std::string matchName, std::shared_ptr<GameMap> gameMap, bool* playing) : 
teams(teams), playerInfoQueue(playerInfoQueue), matchName(matchName), gameMap(gameMap), playing(playing) {
    numberOfPlayers = gameMap->getNumberTeams();
}


void Match::run() {
    int idPlayer = 0;
    Queue<std::shared_ptr<Command>> commandQueue(90);
    StatusBroadcaster statusBroadcaster;
    while (idPlayer != numberOfPlayers) {

        // bloqueo el while con un pop de la queue de InfoStruct
        std::shared_ptr<InfoStruct> infoStruct = playerInfoQueue->pop();

        // le seteo el team al GameMap y lo uso para crear el nuevo Player
        std::shared_ptr<GameMap> playerMap = std::make_shared<GameMap>(idPlayer, numberOfPlayers, gameMap->getMapName(), gameMap->getBeams(), gameMap->getWorms());
        Player* player = new Player(infoStruct->prot, commandQueue, playerMap);
        std::cout << "Creo al player!\n";
        statusBroadcaster.addPlayer(idPlayer, player->getPlayerQueue());
        players.push_back(player);
        player->start();
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
