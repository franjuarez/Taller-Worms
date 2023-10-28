#include "client.h"
#include "../shared_src/constants.h"


Client::Client(const std::string& servname, const std::string& hostname) :
protocol(servname, hostname), sender(protocol),
receiver(protocol, std::ref(gameStatusQueue)){}

GameStatus& Client::getGameStatus() {
    GameMap gameMap(0, ""); GameDynamic gameDynamic(NO_WORM_PLAYING);
    GameStatus gameStatus(false, gameMap, gameDynamic);
    gameStatusQueue.try_pop(gameStatus);
    return gameStatus;
}

Client::~Client(){}