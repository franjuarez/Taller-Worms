#include "client.h"
#include "../shared_src/constants.h"


Client::Client(const std::string& servname, const std::string& hostname) :
protocol(servname, hostname), gameDynamic(NO_WORM_PLAYING), 
sender(protocol), receiver(protocol, std::ref(gameStatusQueue)){}

GameDynamic Client::getGameStatus() {
    gameStatusQueue.try_pop(gameDynamic);
    return gameDynamic;
}

Client::~Client(){}